/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 22:52:15 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/21 19:18:01 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
# include <stdio.h>

typedef unsigned char	t_byte;

typedef unsigned int	t_byte32;

typedef struct			s_key
{
	t_byte				k[7];
	t_byte				c[4];
	t_byte				d[4];
}						t_key;

typedef struct			s_init_key
{
	t_byte				bytes[8];
}						t_init_key;

typedef struct			s_data
{
	t_byte				m[8];
	t_byte				r[4];
	t_byte				l[4];
}						t_data;

typedef enum			e_des_action
{
	ENCRYPT,
	DECRYPT
}						t_des_action;

# define GET_NTH_BIT(k, n) (((k)[((n) - 1) / 8] >> (7 - (((n) - 1) % 8))) & 0x1)
# define SET_NTH_BIT(k, n, b) (k)[((n) - 1) / 8] |= (b) << (7 - (((n) - 1) % 8))
# define CLEAR_BIT(k, n) (k)[((n) - 1) / 8] &= ~(1 << (((n) - 1) % 8))

t_byte		g_key_permutation[] = {
	57, 49, 41, 33, 25, 17, 9,
	1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27,
	19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	7, 62, 54, 46, 38, 30, 22,
	14, 6, 61, 53, 45, 37, 29,
	21, 13, 5, 28, 20, 12, 4
};

t_byte		g_key_compression_permutation[] = {
	14, 17, 11, 24, 1, 5,
	3, 28, 15, 6, 21, 10,
	23, 19, 12, 4, 26, 8,
	16, 7, 27, 20, 13, 2,
	41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32
};

t_byte		g_key_shifts[] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

t_byte		g_initial_permutation[] = {
	58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17, 9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7
};

t_byte		g_final_permutation[] = {
	40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41, 9, 49, 17, 57, 25
};

t_byte		g_expansion_permutation[] = 
{
	32, 1, 2, 3, 4, 5,
	4, 5, 6, 7, 8, 9,
	8, 9, 10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32, 1
};

t_byte		g_s_block[8][64] = {
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

t_byte		g_p_block[] = {
	16, 7, 20, 21,
	29, 12, 28, 17,
	1, 15, 23, 26,
	5, 18, 31, 10,
	2, 8, 24, 14,
	32, 27, 3, 9,
	19, 13, 30, 6,
	22, 11, 4, 25,
};

# define DEBUG 1

# define print_key(k, n) \
	do { \
	if (!DEBUG) break; \
	for (int i = 0; i < n; i++)\
	{\
		printf(" %02x", k[i]);\
	} \
	printf("\n");\
	} while(0)

void	initial_key_permutation(const t_init_key key, t_key *out_key)
{
	int		i;
	t_byte	tmp;

	ft_bzero((void*)out_key, sizeof(t_key));
	i = -1;
	while (++i < 64)
	{
		printf("%1d", GET_NTH_BIT(key.bytes, i + 1));
		if ((i + 1) % 4 == 0 && i != 0)
			printf(" ");
	}
	puts(" ");
	i = -1;
	while (++i < 56)
	{
		tmp = GET_NTH_BIT(key.bytes, g_key_permutation[i]);
		if (GET_NTH_BIT(out_key->k, i + 1))
			CLEAR_BIT(out_key->k, i + 1);
		SET_NTH_BIT(out_key->k, i + 1, tmp);
		printf("%1d", GET_NTH_BIT(out_key->k, i + 1));
		if ((i + 1) % 4 == 0 && i != 0)
			printf(" ");
	}
	puts(" ");
	i = -1;
	while (++i < 56)
	{
		if (i < 28)
			SET_NTH_BIT(out_key->c, i + 1, GET_NTH_BIT(out_key->k, i + 1));
		else
			SET_NTH_BIT(out_key->d, i + 1 - 28, GET_NTH_BIT(out_key->k, i + 1));
	}
}

void	left_shift(t_byte *dst, const t_byte *src, int shift)
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

void	right_shift(t_byte *dst, const t_byte *src, int shift)
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

void	compression_key_transformation(t_byte *k, const t_byte *c,
			const t_byte *d)
{
	int		i;
	t_byte	tmp[7];

	i = -1;
	ft_bzero((void*)&(tmp[0]), 7);
	while (++i < 56)
	{
		if (i < 28/*24*/)
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

void	gen_keys(const t_init_key init_key, t_key *keys, t_des_action action)
{
	int				i;
	t_key			*tmp_key;

	tmp_key = &keys[0];
	ft_bzero(tmp_key, sizeof(t_key));
	puts("initial key:");
	print_key(init_key.bytes, 8);
	initial_key_permutation(init_key, tmp_key);
	puts("initial key permutation: K:");
	print_key(tmp_key->k, 7);
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
		/* printf("key number %d:\n", i); */
		compression_key_transformation(&(keys[i + 1].k[0]), &(keys[i + 1].c[0]),
			&(keys[i + 1].d[0]));
	}
}

/*
** apply inital_permutation on 64bits @src
** returns 64bits @dst
*/

void	inital_permutation(t_byte *dst, const t_byte *src)
{
	int		i;

	ft_bzero((void*)dst, sizeof(t_byte) * 8);
	i = -1;
	while (++i < 64)
		SET_NTH_BIT(dst, i + 1, GET_NTH_BIT(src, g_initial_permutation[i]));
}

void	final_permutation(t_byte *dst, const t_byte *src)
{
	int		i;

	i = -1;
	ft_bzero((void*)dst, sizeof(t_byte) * 8);
	while (++i < 64)
		SET_NTH_BIT(dst, i + 1, GET_NTH_BIT(src, g_final_permutation[i]));
}

void	split_data_block(t_data *data)
{
	ft_memcpy((void*)&(data->l[0]), (void*)&(data->m[0]), sizeof(t_byte) * 4);
	ft_memcpy((void*)&(data->r[0]), (void*)&(data->m[4]), sizeof(t_byte) * 4);
}

void	join_data_block(t_data *data)
{
	ft_memcpy((void*)&(data->m[4]), (void*)&(data->l[0]), sizeof(t_byte) * 4);
	ft_memcpy((void*)&(data->m[0]), (void*)&(data->r[0]), sizeof(t_byte) * 4);
}

/*
** @dst should be 6 bytes long
*/

void	expansion_permutation(t_byte *dst, const t_byte *r)
{
	int		i;

	ft_bzero((void*)dst, sizeof(t_byte) * 6);
	i = -1;
	while (++i < 48)
		SET_NTH_BIT(dst, i + 1, GET_NTH_BIT(r, g_expansion_permutation[i]));
}

t_byte	transform_one_s_block(t_byte input, int num)
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

void	s_block_transformation(t_byte *dst, const t_byte *b_blocks)
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

void	f_function(t_byte *dst, const t_byte *r, const t_byte *key)
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

void	des_round(t_data *dst, const t_data *old, t_byte *key)
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

void	des_process_block(t_byte *dst, t_byte *block, t_key *keys,
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
	while ((action == DECRYPT) ? --i > 0 : ++i < 16)
	{
		des_round(&data, &prev_step, &(keys[i + 1].k[0]));
		ft_memcpy((void*)&(prev_step.l[0]), (void*)&(data.l[0]), 4);
		ft_memcpy((void*)&(prev_step.r[0]), (void*)&(data.r[0]), 4);
	}
	ft_bzero((void*)dst, sizeof(t_byte) * 8);
	join_data_block(&data);
	final_permutation(dst, &(data.m[0]));
}

int		main()
{
	t_init_key		key = {
		{0x13, 0x34, 0x57, 0x79, 0x9b, 0xbc, 0xdf, 0xf1}
		/* {0x31, 0x43, 0x75, 0x97, 0xb9, 0xcb, 0xfd, 0x1f} */
		/* {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff} */
	};
	t_key			keys[17] = {0};
	t_byte			data[8] = {
		/* 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff */
		/* 0x31, 0x43, 0x75, 0x97, 0xb9, 0xcb, 0xfd, 0x1f */
		0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef
	};
	t_byte			out[8] = {0};

	gen_keys(key, &(keys[0]), ENCRYPT);

	ft_bzero((void*)&(out[0]), 8);
	puts("key:");
	print_key(keys[0].k, 7);
	puts("in data:");
	print_key(data, 8);
	des_process_block(&(out[0]), &(data[0]), &(keys[0]), ENCRYPT);
	puts("out:");
	print_key(out, 8);

	ft_bzero((void*)&(data[0]), 8);
	puts("begin decrypt");
	gen_keys(key, &(keys[0]), DECRYPT);
	puts("in data:");
	print_key(out, 8);
	des_process_block(&(data[0]), &(out[0]), &(keys[0]), DECRYPT);
	puts("out:");
	print_key(data, 8);
/* t_byte		c[4] = { */
/* 	0xf3, 0xf3, 0xf3, 0x30 */
/* }; */
/* print_key(c, 4); */
/* t_byte		c_shifted[4] = {0}; */
/* right_shift(&(c_shifted[0]), &(c[0]), 2); */
/* print_key(c_shifted, 4); */
	return (0);
}
