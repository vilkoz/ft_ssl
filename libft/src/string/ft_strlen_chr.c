/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_chr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vitaliirybalko <vrybalko@student.uni       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 15:16:55 by vitaliir          #+#    #+#             */
/*   Updated: 2017/11/21 15:19:11 by vitaliir         ###   ########.fr       */
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
