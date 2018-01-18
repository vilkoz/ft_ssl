/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_arr_quote.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 19:55:32 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/18 19:55:34 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		char_strlen(char const *s, char const *c, int i)
{
	int		n;

	n = 0;
	while (!ft_strchr(c, s[i]) && s[i] != '\0')
	{
		i++;
		n++;
	}
	return (i);
}

static int		count_words(char const *s, char const *c)
{
	int	i;
	int	n;

	i = -1;
	n = 0;
	while (s[++i])
	{
		if (s[i] == '"')
		{
			n++;
			while (s[i] != '"' && s[i] != '\0')
				i++;
		}
		if (!ft_strchr(c, s[i]) && (ft_strchr(c, s[i + 1]) || s[i + 1] == '\0'))
			n++;
	}
	return (n);
}

static char		*put_word(char const *s, char const *c, int *i)
{
	char	*word;
	char	flag;
	int		j;

	flag = 0;
	if (s[*i] == '"')
	{
		c = "\"";
		(*i)++;
		flag = 1;
	}
	if ((word = (char *)malloc(sizeof(char) * (char_strlen(s, c, *i) + 1))))
	{
		j = 0;
		while (!ft_strchr(c, s[*i]) && s[*i])
		{
			word[j] = s[*i];
			(*i)++;
			j++;
		}
		word[j] = '\0';
		(*i) += s[*i] ? flag : 0;
		return (word);
	}
	return (NULL);
}

char			**ft_strsplit_arr_quote(char const *s, char const *c)
{
	char	**out;
	int		i;
	int		j;

	if (s == NULL || !c)
		return (0);
	i = 0;
	j = 0;
	if ((out = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1))) == 0)
		return (0);
	while (s[i])
	{
		if (!ft_strchr(c, s[i]))
		{
			if ((out[j] = put_word(s, c, &i)) == NULL)
				return (NULL);
			j++;
		}
		else
			i++;
	}
	out[j] = NULL;
	return (out);
}
