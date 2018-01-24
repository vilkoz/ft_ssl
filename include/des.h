/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:33:08 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/25 00:50:58 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_H
# define DES_H

# include <stdlib.h>
# include "argparse_struct.h"

typedef unsigned char	t_byte;

typedef struct			s_init_key
{
	t_byte				bytes[8];
}						t_init_key;

typedef struct			s_byte_array
{
	t_byte				*bytes;
	size_t				len;
}						t_byte_array;

# define BYTE_ARRAY(b, l) (t_byte_array){b, l}

typedef struct			s_key
{
	t_byte				k[7];
	t_byte				c[4];
	t_byte				d[4];
}						t_key;

typedef enum			e_des_action
{
	ENCRYPT,
	DECRYPT
}						t_des_action;

void					des_argparse(int ac, char **av, void **data_struct,
							struct s_args *args);

void					des_run(void *arg);

void					des_process_block(t_byte *dst, t_byte *block,
							t_key *keys, t_des_action action);

/*
** generates 17 des keys from @init_key, @keys should have space for 17x56bits
** @action is only required to be equal ENCRYPT
*/

void					gen_keys(const t_init_key init_key, t_key *keys,
							t_des_action action);

/*
** @key and @iv should be 8bytes long
*/

char					*des_encrypt(t_byte_array in, t_byte *key, t_byte *iv);
char					*des_decrypt(t_byte_array in, t_byte *key, t_byte *iv);

#endif
