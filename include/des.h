/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 19:33:08 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/21 20:10:17 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_H
# define DES_H

typedef unsigned char	t_byte;

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


void			des_process_block(t_byte *dst, t_byte *block, t_key *keys,
					t_des_action action);

#endif
