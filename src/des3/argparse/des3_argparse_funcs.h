/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3_argparse_funcs.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 17:00:14 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/31 17:20:30 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES3_ARGPARSE_FUNCS_H
# define DES3_ARGPARSE_FUNCS_H

int	des3_argparse_set_keyarg(int ac, char **av, void *data, int *j);
int	des3_cbc_argparse_set_iv(int ac, char **av, void *data, int *j);
int	des3_argparse_set_decode(int ac, char **av, void *data, int *j);
int	des3_argparse_set_filein(int ac, char **av, void *data, int *j);
int	des3_argparse_set_fileout(int ac, char **av, void *data, int *j);
int	des3_argparse_set_b64(int ac, char **av, void *data, int *j);

#endif
