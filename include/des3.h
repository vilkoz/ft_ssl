/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 17:51:48 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/29 17:53:26 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES3_H
# define DES3_H

# include "des.h"

void					des3_argparse(int ac, char **av, void **data_struct,
							struct s_args *args);

void					des3_run(void *arg);

/*
** @key should be 24bytes and @iv should be 8bytes long
*/

char					*des3_process_blocks(t_byte_array in, t_byte *key,
							t_byte *iv, t_des_action action);

#endif
