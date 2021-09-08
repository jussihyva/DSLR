/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openssl_connect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:42:37 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/08 18:04:45 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static void	sockaddr_initialize(
							struct sockaddr_in *const sockaddr,
							const char *const hostname,
							const char *const port)
{
	bzero(sockaddr, sizeof(*sockaddr));
	sockaddr->sin_family = AF_INET;
	sockaddr->sin_port = htons(atoi(port));
	sockaddr->sin_addr.s_addr = inet_addr(hostname);
	return ;
}

t_tls_connection	*ft_openssl_connect(
									const char *const hostname,
									const char *const port,
									const int socket_fd,
									SSL_CTX *const ctx)
{
	int					error;
	struct sockaddr_in	sockaddr;
	t_tls_connection	*tls_connection;

	tls_connection = NULL;
	sockaddr_initialize(&sockaddr, hostname, port);
	error = connect(socket_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr));
	if (error != -1)
	{
		tls_connection = ft_memalloc(sizeof(*tls_connection));
		tls_connection->socket_fd = socket_fd;
		tls_connection->ctx = ctx;
		tls_connection->ssl_bio = SSL_new(tls_connection->ctx);
		SSL_set_fd(tls_connection->ssl_bio, tls_connection->socket_fd);
		error = SSL_connect(tls_connection->ssl_bio);
		if (error == -1)
		{
			FT_LOG_WARN("SSL connection error: %d", error);
			ft_openssl_rel_conn(&tls_connection);
		}
	}
	else
		FT_LOG_WARN("Influxdb connection error: %d", error);
	return (tls_connection);
}
