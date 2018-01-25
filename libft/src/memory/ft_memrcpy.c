/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 01:16:10 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/26 01:23:49 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memrcpy(void *dst, const void *src, size_t len)
{
	unsigned char	*s;
	unsigned char	*d;
	size_t			i;

	if (!dst || !src)
		return ((void*)0);
	s = (unsigned char*)src;
	d = (unsigned char*)dst;
	i = 0;
	while (i < len)
	{
		d[i] = s[len - 1 - i];
		i++;
	}
	return (dst);
}
