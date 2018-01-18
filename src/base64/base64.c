/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 23:08:41 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/18 17:49:51 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64_private.h"
#include "libft.h"

static void		bit_field_to_string(char *out, unsigned int field,
		unsigned int empty_bits)
{
	static char		*base64_dict = BASE64_DICT;

	out[3] = empty_bits >= 1 ? '=' : base64_dict[field & 0x3f];
	field = field >> 6;
	out[2] = empty_bits == 1 ? '=' : base64_dict[field & 0x3f];
	field = field >> 6;
	out[1] = base64_dict[field & 0x3f];
	field = field >> 6;
	out[0] = base64_dict[field & 0x3f];
}

char			*base64_encode(char *in)
{
	char				*out;
	int					i;
	int					j;
	t_convert_word		convert_word;

	out = ft_strnew(CEIL_DIV(ft_strlen(in), 3) * 4);
	convert_word.field = 0;
	i = -1;
	j = 0;
	while (in[++i])
	{
		if (i % 3 == 0 && i != 0)
		{
			bit_field_to_string(out + j, convert_word.field, 0);
			j += 4;
			convert_word.field = 0;
		}
		convert_word.byte[2 - (i % 3)] = in[i];
	}
	bit_field_to_string(out + j, convert_word.field, i % 3);
	return (out);
}

static char		b64_char_to_num(char c)
{
	static char			*base64 = BASE64_DICT;

	return (c != '=' ? ft_strchr(base64, c) - base64 : 0);
}

char			*base64_decode(char *in)
{
	char				*out;
	int					i;
	int					j;
	t_convert_word		convert_word;

	out = ft_strnew(CEIL_DIV(ft_strlen(in), 4) * 3);
	convert_word.field = 0;
	i = -1;
	j = 0;
	while (in[++i])
	{
		if (i % 4 == 0 && i != 0)
		{
			REV_B64_CHAR(convert_word.byte);
			ft_strncpy(out + j, (char*)convert_word.byte, 3);
			j += 3;
			convert_word.field = 0;
		}
		SET_B64_CHAR(convert_word.field, b64_char_to_num(in[i]), 3 - (i % 4));
	}
	REV_B64_CHAR(convert_word.byte);
	ft_strncpy(out + j, (char*)convert_word.byte, 3);
	return (out);
}
