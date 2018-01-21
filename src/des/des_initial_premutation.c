/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_initial_premutation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:55:09 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/21 20:11:43 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des_private.h"
#include "libft.h"

static t_byte	g_initial_permutation[] = {
	58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17, 9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7
};

static t_byte	g_final_permutation[] = {
	40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41, 9, 49, 17, 57, 25
};

static t_byte	g_expansion_permutation[] = 
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


/*
** apply inital_permutation on 64bits @src
** returns 64bits @dst
*/

void			inital_permutation(t_byte *dst, const t_byte *src)
{
	int		i;

	ft_bzero((void*)dst, sizeof(t_byte) * 8);
	i = -1;
	while (++i < 64)
		SET_NTH_BIT(dst, i + 1, GET_NTH_BIT(src, g_initial_permutation[i]));
}

void			final_permutation(t_byte *dst, const t_byte *src)
{
	int		i;

	i = -1;
	ft_bzero((void*)dst, sizeof(t_byte) * 8);
	while (++i < 64)
		SET_NTH_BIT(dst, i + 1, GET_NTH_BIT(src, g_final_permutation[i]));
}

void			split_data_block(t_data *data)
{
	ft_memcpy((void*)&(data->l[0]), (void*)&(data->m[0]), sizeof(t_byte) * 4);
	ft_memcpy((void*)&(data->r[0]), (void*)&(data->m[4]), sizeof(t_byte) * 4);
}

void			join_data_block(t_data *data)
{
	ft_memcpy((void*)&(data->m[4]), (void*)&(data->l[0]), sizeof(t_byte) * 4);
	ft_memcpy((void*)&(data->m[0]), (void*)&(data->r[0]), sizeof(t_byte) * 4);
}

/*
** @dst should be 6 bytes long
*/

void			expansion_permutation(t_byte *dst, const t_byte *r)
{
	int		i;

	ft_bzero((void*)dst, sizeof(t_byte) * 6);
	i = -1;
	while (++i < 48)
		SET_NTH_BIT(dst, i + 1, GET_NTH_BIT(r, g_expansion_permutation[i]));
}

