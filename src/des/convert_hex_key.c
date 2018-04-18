/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_hex_key.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:34:06 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/19 02:01:33 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** @dst should be 8bytes long
*/

int				convert_hex_key(unsigned char *dst, const char *src)
{
	unsigned char		arg[17];
	unsigned char		half[9];
	int					tmp;
	int					i;

	if (!dst || !src)
		return (-1);
	i = -1;
	while (src[++i] && i < 8)
		if (!ft_isdigit(src[i]) && !(ft_tolower(src[i]) >= 'a'
					&& ft_tolower(src[i]) <= 'f'))
			return (-src[i]);
	ft_bzero((void*)dst, 8);
	ft_bzero((void*)&(arg[0]), 17);
	ft_memset((void*)&(arg[0]), '0', 16);
	ft_memcpy((void*)&(arg[0]), (void*)(src),
			ft_strlen(src) < 16 ? ft_strlen(src) : 16);
	ft_bzero((void*)&(half[0]), 9);
	ft_memcpy((void*)&(half[0]), (void*)&(arg[0]), 8);
	tmp = ft_atoi_base((char*)&(half[0]), 16);
	ft_memrcpy((void*)dst, &tmp, 4);
	ft_memcpy((void*)&(half[0]), (void*)&(arg[8]), 8);
	tmp = ft_atoi_base((char*)&(half[0]), 16);
	ft_memrcpy((void*)(dst + 4), &tmp, 4);
	return (0);
}
