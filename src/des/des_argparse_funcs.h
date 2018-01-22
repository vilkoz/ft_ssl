/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_argparse_funcs.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 01:09:02 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/22 01:10:31 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_ARGPARSE_FUNCS_H
# define DES_ARGPARSE_FUNCS_H

# include "des_argparse_private.h"

int	des_argparse_set_decode(int ac, char **av, t_des_config *data, int j);
int	des_argparse_set_filein(int ac, char **av, t_des_config *data, int j);
int	des_argparse_set_fileout(int ac, char **av, t_des_config *data, int j);
int	des_argparse_set_b64(int ac, char **av, t_des_config *data, int j);
int	des_argparse_set_keyarg(int ac, char **av, t_des_config *data, int j);

#endif
