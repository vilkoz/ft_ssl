/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_argparse_funcs.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 01:09:02 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/25 01:37:55 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_ARGPARSE_FUNCS_H
# define DES_ARGPARSE_FUNCS_H

# include "des_argparse_private.h"

int	des_argparse_set_decode(int ac, char **av, void *data, int j);
int	des_argparse_set_filein(int ac, char **av, void *data, int j);
int	des_argparse_set_fileout(int ac, char **av, void *data, int j);
int	des_argparse_set_b64(int ac, char **av, void *data, int j);
int	des_argparse_set_keyarg(int ac, char **av, void *data, int j);
int	des_cbc_argparse_set_iv(int ac, char **av, void *data, int j);

#endif
