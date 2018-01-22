/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 21:35:00 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/23 00:55:41 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include "libft.h"
# include <stdio.h>

static void		process_block(char *out, const t_byte_array in, t_key *keys,
					t_des_action action)
{
	t_byte		tmp[8];

	ft_bzero((void*)&(tmp[0]), 8);
	ft_memcpy((void*)&(tmp[0]), (void*)in.bytes, in.len);
	des_process_block((t_byte*)out, &(tmp[0]), keys, action);
}

static char		*des_ecb(t_byte_array in, t_byte *key, t_des_action action)
{
	int				i;
	char			*out;
	t_key			keys[17];
	t_init_key		init_key;

	ft_memcpy((void*)&(init_key.bytes[0]), (void*)key, 8);
	gen_keys(init_key, &(keys[0]), ENCRYPT);
	out = ft_strnew(in.len + (8 - in.len % 8));
	i = -8;
	while ((size_t)(i+=8) < in.len)
	{
		if (action == DECRYPT && (in.len % 8 != 0) && (size_t)(i + 8) >= in.len)
		{
			ft_putendl_fd("ft_ssl: des: bad_block!", 2);
			break ;
		}
		process_block(out + i, BYTE_ARRAY((in.bytes + i),
					(size_t)(i + 8) >= in.len ? in.len - (size_t)(i): 8),
				&(keys[0]), action);
	}
	return (out);
}

/*
** @key and @iv should be 8bytes long
*/

char			*des_encrypt(t_byte_array in, t_byte *key, t_byte *iv)
{
	(void)iv;
	return (des_ecb(in, key, ENCRYPT));
}

char			*des_decrypt(t_byte_array in, t_byte *key, t_byte *iv)
{
	(void)iv;
	return (des_ecb(in, key, DECRYPT));
}
