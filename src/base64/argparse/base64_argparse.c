/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_argparse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 13:06:43 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/25 00:55:49 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64_argparse_private.h"
#include "argparse_struct.h"
#include "libft.h"

static char		*g_flags[NUMBER_OF_FLAGS] = {
	"-d",
	"-e",
	NULL,
	"-i",
	NULL,
	"-o"
};

static int		(*g_funcs[NUMBER_OF_FLAGS])(int,
					char **, void *, int) = {
	base64_argparse_set_decode,
	base64_argparse_set_encode,
	NULL,
	base64_argparse_set_filein,
	NULL,
	base64_argparse_set_fileout
};

void			base64_argparse(int ac, char **av, void **data_struct,
					t_args *args)
{
	t_base64_config		*data;

	(void)ac;
	(void)av;
	data = (t_base64_config*)ft_memalloc(sizeof(t_base64_config));
	data->mode = ENCODE;
	data->in_mode = STDIN;
	data->in_fd = 0;
	data->out_mode = STDOUT;
	data->out_fd = 1;
	*data_struct = (void*)data;
	args->flags_num = NUMBER_OF_FLAGS;
	args->funcs = &(g_funcs[0]);
	args->flags = &(g_flags[0]);
}
