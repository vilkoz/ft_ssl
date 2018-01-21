/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 22:52:15 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/21 20:12:02 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "des_private.h"

static t_byte	g_s_block[8][64] = {
	{
		14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
		0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
		4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
		15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13
	},
	{
		15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
		3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
		0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
		13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9
	},
	{
		10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
		13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
		13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
		1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12
	},
	{
		7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
		13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
		10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
		3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14
	},
	{
		2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
		14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
		4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
		11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3
	},
	{
		12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
		10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
		9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
		4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13
	},
	{
		4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
		13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
		1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
		6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12
	},
	{
		13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
		1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
		7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
		2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11
	}
};

static t_byte	g_p_block[] = {
	16, 7, 20, 21,
	29, 12, 28, 17,
	1, 15, 23, 26,
	5, 18, 31, 10,
	2, 8, 24, 14,
	32, 27, 3, 9,
	19, 13, 30, 6,
	22, 11, 4, 25,
};

static t_byte	transform_one_s_block(t_byte input, int num)
{
	t_byte	x;
	t_byte	y;

	y = (input >> 4 & 0x2) | (input & 0x1);
	x = (input >> 1) & 15;
	return (g_s_block[num][y * 16 + x]);
}

/*
** takes @b_blocks 48bit (6 byte), returns to @dst 32bit (4 byte)
*/

static void		s_block_transformation(t_byte *dst, const t_byte *b_blocks)
{
	int		i;
	int		j;
	int		s;
	t_byte	res[1];
	t_byte	input[1];

	i = -1;
	input[0] = 0;
	ft_bzero((void*)dst, sizeof(t_byte) * 4);
	while (++i <= 48)
	{
		if (i % 6 == 0 && i != 0)
		{
			s = (i - 1) / 6;
			res[0] = 0;
			res[0] = transform_one_s_block(input[0], s);
			j = - 1;
			while (++j < 4)
				SET_NTH_BIT(dst, j + 1 + s * 4, ((res[0] >> (3 - j)) & 0x1));
			input[0] = 0;
		}
		if (i != 48)
			SET_NTH_BIT(input, (i % 6) + 2 + 1, GET_NTH_BIT(b_blocks, i + 1));
	}
}

/*
** @dst should be 32bits, @r - 32bits, @key - 48bits
** P(S(Kn + E(Rn-1)))
*/

static void		f_function(t_byte *dst, const t_byte *r, const t_byte *key)
{
	t_byte		re[6];
	t_byte		xored[6];
	int			i;

	expansion_permutation(&(re[0]), r);
	ft_bzero((void*)&(xored[0]), sizeof(t_byte) * 6);
	i = -1;
	while (++i < 6)
		xored[i] = key[i] ^ re[i];
	s_block_transformation(&(re[0]), &(xored[0]));
	ft_bzero((void*)&(xored[0]), sizeof(t_byte) * 6);
	i = -1;
	while (++i < 32)
		SET_NTH_BIT(xored, i + 1, GET_NTH_BIT(re, g_p_block[i]));
	ft_memcpy((void*)dst, (void*)&(xored[0]), sizeof(t_byte) * 4);
}

static void		des_round(t_data *dst, const t_data *old, t_byte *key)
{
	int		i;
	t_byte	f_out[4];

	ft_bzero((void*)&(dst->l[0]), 4);
	ft_bzero((void*)&(dst->r[0]), 4);
	ft_memcpy((void*)&(dst->l[0]), (void*)&(old->r[0]), sizeof(t_byte) * 4);
	f_function(&(f_out[0]), &(old->r[0]), key);
	i = -1;
	while (++i < 4)
		f_out[i] ^= old->l[i];
	ft_memcpy((void*)&(dst->r[0]), (void*)&(f_out[0]), sizeof(t_byte) * 4);
}

void			des_process_block(t_byte *dst, t_byte *block, t_key *keys,
					t_des_action action)
{
	int		i;
	t_data	data;
	t_data	prev_step;

	inital_permutation(&(data.m[0]), block);
	split_data_block(&data);
	ft_memcpy((void*)&(prev_step.l[0]), (void*)&(data.l[0]), 4);
	ft_memcpy((void*)&(prev_step.r[0]), (void*)&(data.r[0]), 4);
	i = (action == DECRYPT) ? 15 + 1 : -1;
	while ((action == DECRYPT) ? --i >= 0 : ++i < 16)
	{
		des_round(&data, &prev_step, &(keys[i + 1].k[0]));
		ft_memcpy((void*)&(prev_step.l[0]), (void*)&(data.l[0]), 4);
		ft_memcpy((void*)&(prev_step.r[0]), (void*)&(data.r[0]), 4);
	}
	ft_bzero((void*)dst, sizeof(t_byte) * 8);
	join_data_block(&data);
	final_permutation(dst, &(data.m[0]));
}
