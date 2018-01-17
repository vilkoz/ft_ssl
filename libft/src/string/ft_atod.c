/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/23 23:46:52 by vrybalko          #+#    #+#             */
/*   Updated: 2017/05/23 23:41:36 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_nums(const char *s)
{
	int		i;

	i = -1;
	while (ft_isdigit(s[++i]))
		;
	i++;
	while (s[--i] == '0')
		;
	return (i);
}

static double	ft_pow(double x, int c)
{
	double	res;

	res = 1;
	while (c)
	{
		res *= x;
		c--;
	}
	return (res);
}

static char		*drop_num(const char *s)
{
	int		i;

	i = -1;
	while (ft_isdigit(s[i++]) || s[i] == '-' || s[i] == '+')
		;
	return ((char*)&s[i]);
}

static char		*drop_spaces(char const *s)
{
	int		i;

	i = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	return ((char *)&s[i]);
}

double			ft_atod(const char *s)
{
	int		a;
	int		b;
	int		is_neg;
	char	*minus;
	char	*dot;

	is_neg = 0;
	if ((a = ft_atoi(s)) == 0 &&
		(minus = ft_strtrim(s)) && minus[0] == '-')
		is_neg = 1;
	if (a == 0)
		ft_strdel(&minus);
	if ((dot = ft_strchr(s, '.')) && dot == drop_num(drop_spaces(s)) + 1)
	{
		b = ft_atoi(ft_strchr(s, '.') + 1);
		return (((double)a + (a < 0 ? -1 : 1) * ((double)b /
			(double)ft_pow(10, count_nums(ft_strchr(s, '.') + 1)))) *
			(is_neg && a == 0 ? -1. : 1.));
	}
	return ((double)a);
}
