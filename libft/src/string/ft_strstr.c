/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 21:53:06 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/23 00:11:53 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *s, char *to_find)
{
	int		i;
	size_t	len;
	
	i = -1;
	len = ft_strlen(to_find);
	if (!s || !to_find)
		return (0);
	if (len == 0)
		return ((char*)s);
	while (s[++i])
	{
		if (!ft_strncmp(s + i, to_find, len))
			return ((char*)s + i);
	}
	return (0);
}
