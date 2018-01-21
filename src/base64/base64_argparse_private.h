/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_argparse_private.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 14:20:06 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/21 23:44:59 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE64_ARGPARSE_PRIVATE_H
# define BASE64_ARGPARSE_PRIVATE_H

# ifndef NULL
#  define NULL (void*)0
# endif

# include <stdio.h>
# include <fcntl.h>
# include "base64_argparse_funcs.h"

enum			e_args_flags
{
	DECODE,
	ENCODE,
	STDIN,
	FILEIN,
	STDOUT,
	FILEOUT,
	NUMBER_OF_FLAGS
};

typedef struct	s_base64_config
{
	char		mode;
	char		in_mode;
	char		out_mode;
	int			in_fd;
	int			out_fd;
}				t_base64_config;

#endif
