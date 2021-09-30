/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_path_create.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 09:19:46 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/30 09:20:42 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

char	*ft_file_path_create(char *file_name)
{
	char			*file_path;
	size_t			str_len;

	str_len = ft_strlen(ft_home_dir()) + 1 + ft_strlen(file_name);
	file_path = ft_memalloc(sizeof(*file_path) * (str_len + 1));
	ft_strcat(file_path, ft_home_dir());
	ft_strcat(file_path, "/");
	ft_strcat(file_path, file_name);
	return (file_path);
}
