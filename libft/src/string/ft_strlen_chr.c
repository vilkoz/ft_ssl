/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_chr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 19:54:26 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/18 19:54:28 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlen_chr(char const *s, char const *c)
{
	size_t		i;

	i = 0;
	while (s[i] && !ft_strchr(c, s[i]))
	{
		i++;
	}
	return (i);
}
