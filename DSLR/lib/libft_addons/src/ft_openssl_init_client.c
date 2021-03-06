/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openssl_init_client.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:20:56 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/09 13:43:42 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

SSL_CTX	*ft_openssl_init_client(
					char *pem_cert_file,
					char *pem_private_key_file,
					int *socket_fd,
					const t_connection_protocol influxdb_connection_protocol)
{
	SSL_CTX				*ctx;
	const SSL_METHOD	*tls_method;

	ctx = NULL;
	*socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (*socket_fd != -1)
	{
		if (influxdb_connection_protocol == E_TLS)
		{
			tls_method = TLS_client_method();
			ctx = ft_openssl_init_ctx(tls_method, pem_cert_file,
					pem_private_key_file);
			if (!ctx)
				close(*socket_fd);
		}
	}
	return (ctx);
}
