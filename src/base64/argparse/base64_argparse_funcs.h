/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_argparse_funcs.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 16:11:36 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/25 00:27:52 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE64_ARGPARSE_FUNCS_H
# define BASE64_ARGPARSE_FUNCS_H

struct s_base64_config;

int		base64_argparse_set_decode(int ac, char **av,
			void *data, int j);
int		base64_argparse_set_encode(int ac, char **av,
			void *data, int j);
int		base64_argparse_set_filein(int ac, char **av,
			void *data, int j);
int		base64_argparse_set_fileout(int ac, char **av,
			void *data, int j);

#endif
