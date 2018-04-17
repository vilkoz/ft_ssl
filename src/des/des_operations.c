/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 21:35:00 by vrybalko          #+#    #+#             */
/*   Updated: 2018/04/17 22:25:21 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des.h"
#include "libft.h"
#include "des_operations_private.h"

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
	while ((size_t)(i += 8) < in.len)
	{
		if (action == DECRYPT && (in.len % 8 != 0) && (size_t)(i + 8) >= in.len)
		{
			ft_putendl_fd("ft_ssl: des: bad_block!", 2);
			exit(1);
			break ;
		}
		process_block(out + i, BYTE_ARRAY((in.bytes + i),
				(size_t)(i + 8) >= in.len ? in.len - (size_t)(i) : 8),
				CBC_CONTEXT(&(keys[0]), NULL), action);
	}
	return (out);
}

static char		*des_cbc(t_byte_array in, t_byte *key, t_des_action action,
					t_byte *iv)
{
	int				i;
	char			*out;
	t_key			keys[17];
	t_init_key		init_key;

	ft_memcpy((void*)&(init_key.bytes[0]), (void*)key, 8);
	gen_keys(init_key, &(keys[0]), ENCRYPT);
	out = ft_strnew(in.len + (8 - in.len % 8));
	i = -8;
	while ((size_t)(i += 8) < in.len)
	{
		if (action == DECRYPT && (in.len % 8 != 0) && (size_t)(i + 8) >= in.len)
		{
			ft_putendl_fd("ft_ssl: des: bad_block!", 2);
			break ;
		}
		process_block(out + i, BYTE_ARRAY((in.bytes + i),
			(size_t)(i + 8) >= in.len ? in.len - (size_t)(i) : 8),
			CBC_CONTEXT(&(keys[0]), iv), action);
	}
	return (out);
}

/*
** @key and @iv should be 8bytes long
*/

char			*des_process_blocks(t_byte_array in, t_byte *key, t_byte *iv,
					t_des_action action)
{
	if (iv == NULL)
		return (des_ecb(in, key, action));
	else
		return (des_cbc(in, key, action, iv));
}
