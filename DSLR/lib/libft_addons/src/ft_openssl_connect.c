/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openssl_connect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:42:37 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/09 15:51:22 by jkauppi          ###   ########.fr       */
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

t_tcp_connection	*ft_openssl_connect(
									const char *const hostname,
									const char *const port,
									const int socket_fd,
									SSL_CTX *const ctx)
{
	int					error;
	struct sockaddr_in	sockaddr;
	t_tcp_connection	*tcp_connection;

	tcp_connection = NULL;
	sockaddr_initialize(&sockaddr, hostname, port);
	error = connect(socket_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr));
	if (error != -1)
	{
		tcp_connection = ft_memalloc(sizeof(*tcp_connection));
		tcp_connection->socket_fd = socket_fd;
		if (ctx)
		{
			tcp_connection->ctx = ctx;
			tcp_connection->ssl_bio = SSL_new(tcp_connection->ctx);
			SSL_set_fd(tcp_connection->ssl_bio, tcp_connection->socket_fd);
			error = SSL_connect(tcp_connection->ssl_bio);
			if (error == -1)
			{
				FT_LOG_WARN("SSL connection error: %d", error);
				ft_openssl_rel_conn(&tcp_connection);
			}
		}
	}
	else
		FT_LOG_WARN("Influxdb connection error: %d", error);
	return (tcp_connection);
}
