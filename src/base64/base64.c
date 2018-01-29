/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 23:08:41 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/29 20:57:32 by vrybalko         ###   ########.fr       */
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

char			*base64_encode(unsigned char *in, size_t len)
{
	char				*out;
	int					i;
	int					j;
	t_convert_word		convert_word;

	out = ft_strnew(CEIL_DIV(len, 3) * 4);
	convert_word.field = 0;
	i = -1;
	j = 0;
	while ((size_t)++i < len)
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

static char		*b64_sanitize(char *in, size_t *len)
{
	int		i;
	int		j;
	int		count;
	char	*out;

	count = 0;
	*len = 0;
	i = -1;
	while (in[++i])
		if (ft_strchr(BASE64_DICT, in[i]) || in[i] == '=')
			count++;
	out = ft_strnew(count);
	i = -1;
	j = 0;
	while (in[++i])
	{
		if (ft_strchr(BASE64_DICT, in[i]) || in[i] == '=')
		{
			out[j] = in[i];
			j++;
			(in[i] != '=') ? (*len)++ : 0;
		}
	}
	*len = (size_t)(((float)*len / 4.0) * 3.0);
	return (out);
}

char			*base64_decode(char *in, size_t *len)
{
	char				*out;
	int					i;
	int					j;
	t_convert_word		convert_word;

	in = b64_sanitize(in, len);
	out = ft_strnew(CEIL_DIV(ft_strlen(in), 4) * 3);
	convert_word.field = 0;
	i = -1;
	j = 0;
	while (in[++i])
	{
		if (i % 4 == 0 && i != 0)
		{
			REV_B64_CHAR(convert_word.byte);
			ft_memcpy((void*)(out + j), (void*)convert_word.byte, 3);
			j += 3;
			convert_word.field = 0;
		}
		SET_B64_CHAR(convert_word.field, b64_char_to_num(in[i]), 3 - (i % 4));
	}
	REV_B64_CHAR(convert_word.byte);
	ft_memcpy((void*)(out + j), (void*)convert_word.byte, 3);
	ft_memdel((void*)&in);
	return (out);
}
