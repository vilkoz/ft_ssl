/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_key_generation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:41:03 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/21 20:11:40 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des_private.h"
#include "libft.h"

static t_byte	g_key_permutation[] = {
	57, 49, 41, 33, 25, 17, 9,
	1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27,
	19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	7, 62, 54, 46, 38, 30, 22,
	14, 6, 61, 53, 45, 37, 29,
	21, 13, 5, 28, 20, 12, 4
};

static t_byte	g_key_compression_permutation[] = {
	14, 17, 11, 24, 1, 5,
	3, 28, 15, 6, 21, 10,
	23, 19, 12, 4, 26, 8,
	16, 7, 27, 20, 13, 2,
	41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32
};

static t_byte	g_key_shifts[] = {
	1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

static void		initial_key_permutation(const t_init_key key, t_key *out_key)
{
	int		i;
	t_byte	tmp;

	ft_bzero((void*)out_key, sizeof(t_key));
	i = -1;
	while (++i < 56)
	{
		tmp = GET_NTH_BIT(key.bytes, g_key_permutation[i]);
		if (GET_NTH_BIT(out_key->k, i + 1))
			CLEAR_BIT(out_key->k, i + 1);
		SET_NTH_BIT(out_key->k, i + 1, tmp);
	}
	i = -1;
	while (++i < 56)
	{
		if (i < 28)
			SET_NTH_BIT(out_key->c, i + 1, GET_NTH_BIT(out_key->k, i + 1));
		else
			SET_NTH_BIT(out_key->d, i + 1 - 28, GET_NTH_BIT(out_key->k, i + 1));
	}
}

static void		left_shift(t_byte *dst, const t_byte *src, int shift)
{
	t_byte		save_byte;
	t_byte		first_byte;

	if (shift == 0)
		ft_memcpy((void*)dst, (void*)src, 4);
	first_byte = src[0];
	dst[3] = (src[3] << shift) | (first_byte >> (8 - shift - 4));
	dst[3] ^= dst[3] & 0xf;
	save_byte = src[3];
	dst[2] = (src[2] << shift) | (save_byte >> (8 - shift));
	save_byte = src[2];
	dst[1] = (src[1] << shift) | (save_byte >> (8 - shift));
	save_byte = src[1];
	dst[0] = (src[0] << shift) | (save_byte >> (8 - shift));
}

static void		right_shift(t_byte *dst, const t_byte *src, int shift)
{
	t_byte		save_byte;
	t_byte		first_byte;
	t_byte		mask;

	if (shift == 0)
	{
		ft_memcpy((void*)dst, (void*)src, 4);
		return ;
	}
	mask = (shift == 2) ? 0x3 : 0x1;
	first_byte = src[3];
	dst[0] = (src[0] >> shift) | (((first_byte >> 4) & mask) << (8 - shift));
	save_byte = src[0];
	dst[1] = (src[1] >> shift) | ((save_byte & mask) << (8 - shift));
	save_byte = src[1];
	dst[2] = (src[2] >> shift) | ((save_byte & mask) << (8 - shift));
	save_byte = src[2];
	dst[3] = (src[3] >> shift) | ((save_byte & (mask)) << (8 - shift));
	dst[3] ^= dst[3] & 0xf;
}

/*
** @k - key_destination should be 48bit
*/

static void		compression_key_transformation(t_byte *k, const t_byte *c,
					const t_byte *d)
{
	int		i;
	t_byte	tmp[7];

	i = -1;
	ft_bzero((void*)&(tmp[0]), 7);
	while (++i < 56)
	{
		if (i < 28)
			SET_NTH_BIT(tmp, i + 1, GET_NTH_BIT(c, i + 1));
		else
			SET_NTH_BIT(tmp, i + 1, GET_NTH_BIT(d, i + 1 - 28));
	}
	ft_bzero((void*)k, sizeof(t_byte) * 7);
	i = -1;
	while (++i < 48)
		SET_NTH_BIT(k, i + 1, GET_NTH_BIT(tmp,
					g_key_compression_permutation[i]));
}

void			gen_keys(const t_init_key init_key, t_key *keys,
					t_des_action action)
{
	int				i;
	t_key			*tmp_key;

	tmp_key = &keys[0];
	ft_bzero(tmp_key, sizeof(t_key));
	initial_key_permutation(init_key, tmp_key);
	i = -1;
	while (++i < 16)
	{
		if (action == ENCRYPT)
		{
			left_shift(&(keys[i + 1].c[0]), &(tmp_key->c[0]), g_key_shifts[i]);
			left_shift(&(keys[i + 1].d[0]), &(tmp_key->d[0]), g_key_shifts[i]);
		}
		else
		{
			right_shift(&(keys[i + 1].c[0]), &(tmp_key->c[0]), g_key_shifts[i]);
			right_shift(&(keys[i + 1].d[0]), &(tmp_key->d[0]), g_key_shifts[i]);
		}
		tmp_key = &keys[i + 1];
		compression_key_transformation(&(keys[i + 1].k[0]), &(keys[i + 1].c[0]),
			&(keys[i + 1].d[0]));
	}
}
