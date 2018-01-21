/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_private.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:34:19 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/21 20:09:48 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_PRIVATE_H
# define DES_PRIVATE_H

# include "des.h"

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

# define GET_NTH_BIT(k, n) (((k)[((n) - 1) / 8] >> (7 - (((n) - 1) % 8))) & 0x1)
# define SET_NTH_BIT(k, n, b) (k)[((n) - 1) / 8] |= (b) << (7 - (((n) - 1) % 8))
# define CLEAR_BIT(k, n) (k)[((n) - 1) / 8] &= ~(1 << (((n) - 1) % 8))

/*
** extern t_byte			g_key_permutation[];
** extern t_byte			g_key_compression_permutation[];
** extern t_byte			g_key_shifts[];
** extern t_byte			g_initial_permutation[];
** extern t_byte			g_final_permutation[];
** extern t_byte			g_expansion_permutation[];
** extern t_byte			g_s_block[8][64];
** extern t_byte			g_p_block[];
*/

/*
** generates 17 des keys from @init_key, @keys should have space for 17x56bits
** @action is only required to be equal ENCRYPT
*/

void					gen_keys(const t_init_key init_key, t_key *keys,
							t_des_action action);

/*
** apply inital_permutation on 64bits @src
** returns 64bits @dst
*/

void					inital_permutation(t_byte *dst, const t_byte *src);

/*
** apply final_permutation on 64bits @src
** returns 64bits @dst
*/

void					final_permutation(t_byte *dst, const t_byte *src);
void					split_data_block(t_data *data);
void					join_data_block(t_data *data);

/*
** @dst should be 6 bytes long
*/

void					expansion_permutation(t_byte *dst, const t_byte *r);

#endif
