/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_influxdb_connect.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 13:20:07 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/07 14:05:35 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static void	set_client_socket_params(const int socket_fd)
{
	t_timeval		timeout;
	int				on;

	timeout.tv_sec = 0;
	timeout.tv_usec = 1;
	on = 1;
	setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
	setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
		sizeof(timeout));
	return ;
}

t_tls_connection	*ft_influxdb_connect(
									const char *const host_name,
									const char *const port_number)
{
	SSL_CTX				*ctx;
	int					socket_fd;
	char				*cert_file;
	char				*private_key_file;
	t_tls_connection	*tls_connection;

	ft_openssl_init();
	cert_file = ft_file_create(ft_home_dir(), PEM_CERT_FILE);
	private_key_file = ft_file_create(ft_home_dir(), PEM_PRIVTE_KEY_FILE);
	ctx = ft_openssl_init_client(cert_file, private_key_file, &socket_fd);
	tls_connection = ft_openssl_connect(host_name, port_number, socket_fd, ctx);
	if (tls_connection)
		set_client_socket_params(socket_fd);
	else
	{
		SSL_CTX_free(ctx);
		FT_LOG_WARN("Connection setup to Influxdb failed!");
	}
	ft_strdel(&cert_file);
	ft_strdel(&private_key_file);
	return (tls_connection);
}
