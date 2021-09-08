/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_influxdb_write.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:03:16 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/08 17:48:09 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static t_bool	response_validate(SSL *const ssl_bio)
{
	char		*read_buf;
	int			chars;
	t_bool		validation_result;

	validation_result = E_FALSE;
	read_buf = (char *)ft_memalloc(sizeof(*read_buf) * SEND_REC_BUF_MAX_SIZE);
	chars = -1;
	while (chars <= 0)
		chars = SSL_read(ssl_bio, read_buf, SEND_REC_BUF_MAX_SIZE);
	if (chars == -1)
		FT_LOG_ERROR("%s", "Reading of influxdb response failed!");
	else
	{
		while (chars > 0)
		{
			FT_LOG_TRACE("CHARS: %s", read_buf);
			if (!ft_strncmp(read_buf, "HTTP/1.1 204", 12))
				validation_result = E_TRUE;
			chars = SSL_read(ssl_bio, read_buf, SEND_REC_BUF_MAX_SIZE);
		}
	}
	ft_strdel(&read_buf);
	return (validation_result);
}

static const char	*create_header(
								const char *const token,
								size_t body_length)
{
	char		*header;

	header = ft_memalloc(sizeof(*header) * SEND_REC_BUF_MAX_SIZE);
	sprintf(header,
		"%s %s%s%sContent-Length: %ld\r\n\r\n",
		"POST /api/v2/write?org=Builders&bucket=Hive&precision=s",
		"HTTP/1.1\r\nHost: None\r\nAuthorization: Token ",
		token, "\r\n", body_length);
	return (header);
}

void	ft_influxdb_write(
						const t_tls_connection *const connection,
						const char *const body,
						const char *const database,
						const char **const influxdb_token_array)
{
	const char	*header;
	t_bool		validation_result;
	size_t		i;
	const char	*token;
	size_t		body_length;

	(void)database;
	body_length = ft_strlen(body);
	if (connection)
	{
		validation_result = E_FALSE;
		i = -1;
		while (!validation_result && ++i < 2)
		{
			token = influxdb_token_array[i];
			header = create_header(token, body_length);
			SSL_write(connection->ssl_bio, header, strlen(header));
			FT_LOG_TRACE("HEADER: %s", header);
			FT_LOG_TRACE("BODY: %s", body);
			SSL_write(connection->ssl_bio, body, strlen(body));
			ft_strdel((char **)&header);
			validation_result = response_validate(connection->ssl_bio);
		}
	}
	return ;
}
