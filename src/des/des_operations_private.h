/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_operations_private.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/26 01:39:20 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/26 01:39:21 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_OPERATIONS_PRIVATE_H
# define DES_OPERATIONS_PRIVATE_H

# include "des.h"

typedef struct	s_cbc_context
{
	t_key		*keys;
	t_byte		*iv;
}				t_cbc_context;

# define CBC_CONTEXT(k, i) (t_cbc_context){k, i}

#endif
