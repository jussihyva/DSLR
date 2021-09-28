/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_home_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 18:02:34 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/27 18:03:25 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dslr.h"

const char	*ft_home_dir(void)
{
	struct passwd	*pw;
	const char		*homedir;

	pw = getpwuid(getuid());
	homedir = pw->pw_dir;
	return (homedir);
}
