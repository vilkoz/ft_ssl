/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 17:34:25 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/29 17:57:53 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include "libft.h"
#include "../des/des_operations_private.h"

static void		process_block(char *out, const t_byte_array in,
					t_cbc_context context, t_des_action action)
{
	t_byte		tmp[8];
	t_byte		save_iv[8];
	int			i;

	ft_bzero((void*)&(tmp[0]), 8);
	ft_memcpy((void*)&(tmp[0]), (void*)in.bytes, in.len);
	i = -1;
	while (context.iv && ++i < 8)
		if (action == ENCRYPT)
			tmp[i] = tmp[i] ^ context.iv[i];
		else
			save_iv[i] = tmp[i];
	des_process_block((t_byte*)out, &(tmp[0]), context.keys, action);
	i = -1;
	while (context.iv && ++i < 8)
	{
		if (action == ENCRYPT)
			context.iv[i] = out[i];
		else
		{
			out[i] = (char)(((t_byte)out[i]) ^ context.iv[i]);
			context.iv[i] = save_iv[i];
		}
	}
}

char			*des3_process_blocks(t_byte_array in, t_byte *key,
					t_des_action action, t_byte *iv)
{
	int				i;
	char			*out;
	t_key			keys[3][17];
	t_init_key		init_key[3];

	ft_memcpy((void*)&(init_key[0].bytes[0]), (void*)key, 8);
	ft_memcpy((void*)&(init_key[1].bytes[0]), (void*)key + 8, 8);
	ft_memcpy((void*)&(init_key[2].bytes[0]), (void*)key + 16, 8);
	gen_keys(init_key[0], &(keys[0][0]), ENCRYPT);
	gen_keys(init_key[1], &(keys[1][0]), ENCRYPT);
	gen_keys(init_key[2], &(keys[2][0]), ENCRYPT);
	out = ft_strnew(in.len + (8 - in.len % 8));
	i = -8;
	while ((size_t)(i += 8) < in.len)
	{
		if (action == DECRYPT && (in.len % 8 != 0) && (size_t)(i + 8) >= in.len)
		{
			ft_putendl_fd("ft_ssl: des: bad_block!", 2);
			break ;
		}
		process_block(out + i, BYTE_ARRAY((in.bytes + i), 8),
			CBC_CONTEXT(&(keys[0][0]), iv), action == ENCRYPT ? ENCRYPT : DECRYPT);
		process_block(out + i, BYTE_ARRAY((unsigned char*)(out + i), 8),
			CBC_CONTEXT(&(keys[1][0]), iv), action == ENCRYPT ? DECRYPT : ENCRYPT);
		process_block(out + i, BYTE_ARRAY((unsigned char*)(out + i), 8),
			CBC_CONTEXT(&(keys[2][0]), iv), action == ENCRYPT ? ENCRYPT : DECRYPT);
	}
	return (out);
}
