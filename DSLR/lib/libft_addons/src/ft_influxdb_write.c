/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_influxdb_write.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 18:03:16 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/07 18:58:24 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static void	read_response(const int socket_fd)
{
	char		*read_buf;
	int			chars;
	clock_t		start;
	clock_t		end;

	read_buf = (char *)ft_memalloc(sizeof(*read_buf) * SEND_REC_BUF_MAX_SIZE);
	start = clock();
	end = start + (CLOCKS_PER_SEC * 2);
	chars = -1;
	while (chars == -1 && end > clock())
		chars = read(socket_fd, read_buf, SEND_REC_BUF_MAX_SIZE);
	if (chars == -1)
		FT_LOG_ERROR("%s", "Reading of influxdb response failed!");
	else
	{
		while (chars > 0)
		{
			FT_LOG_TRACE("CHARS: %s", read_buf);
			chars = read(socket_fd, read_buf, SEND_REC_BUF_MAX_SIZE);
		}
	}
	ft_strdel(&read_buf);
	return ;
}

void	ft_influxdb_write(
						const t_tls_connection *const connection,
						const char *const body,
						const char *const database)
{
	char		header[SEND_REC_BUF_MAX_SIZE];

	if (connection)
	{
		sprintf(header,
			"POST /api/v2/write?org=Builders&bucket=%s&precision=s %sContent-Length: %ld\r\n\r\n",
			database, "HTTP/1.1\r\nHost: None\r\nAuthorization: Token hY8i8qNMkwmZlIIHwNxhiWO_qNKuGuaZvKZBTwYV4PjyvRFYB7gzRImKZm8pqV9-Yvd6PIqC2T0zCbqHwnQ33A==\r\n", strlen(body));
		write(connection->socket_fd, header, strlen(header));
		FT_LOG_TRACE("BODY: %s", header);
		FT_LOG_TRACE("BODY: %s", body);
		write(connection->socket_fd, body, strlen(body));
		read_response(connection->socket_fd);
	}
	return ;
}
