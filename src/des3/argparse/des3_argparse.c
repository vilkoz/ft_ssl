/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3_argparse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:55:24 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/31 18:02:30 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des3_argparse_funcs.h"
#include "des3_argparse_private.h"
#include "libft.h"
#include "argparse_struct.h"

static char		*g_flags[NUMBER_OF_FLAGS] = {
	"-e",
	"-d",
	NULL,
	"-i",
	NULL,
	"-o",
	"-a",
	NULL,
	"-k",
	NULL,
	"-v"
};

static int		(*g_funcs[NUMBER_OF_FLAGS])(int,
					char **, void *, int *) = {
	accept_arg,
	des3_argparse_set_decode,
	NULL,
	des3_argparse_set_filein,
	NULL,
	des3_argparse_set_fileout,
	des3_argparse_set_b64,
	NULL,
	des3_argparse_set_keyarg,
	NULL,
	des3_cbc_argparse_set_iv,
};

static char		*g_help_msg[] = {
	"des3 help:",
	"",
	"des3 is alias for des3-cbc"
	"",
	"usage: ./ft_ssl des3 [-e|-d] [-i file|-o file] [-a] [-k key] [-v iv]",
	"",
	"-e - encrypt mode",
	"-d - decrypt mode",
	"-i - read from file in next argument",
	"-o - write to file in next argument",
	"-a - encode output (if -e) or decode input (if -d) in/from base64",
	"-k - set key in hex (24 bytes or 48 hex chars)",
	"-v - set initial vector in hex (8 bytes or 16 hex chars)",
	NULL
};

void			des3_help(void)
{
	int		i;

	i = -1;
	while (g_help_msg[++i])
		ft_putendl(g_help_msg[i]);
}

void			des3_argparse(int ac, char **av, void **data_struct,
					t_args *args)
{
	t_des3_config		*data;

	(void)ac;
	(void)av;
	data = (t_des3_config*)ft_memalloc(sizeof(t_des3_config));
	data->mode = ENCRYPT_FLAG;
	data->in_mode = STDIN;
	data->in_fd = 0;
	data->out_mode = STDOUT;
	data->out_fd = 1;
	data->b64_mode = NOBASE64;
	data->key_mode = KEY_STDIN;
	data->chiper_mode = CBC;
	ft_bzero((void*)&(data->key[0]), 24);
	*data_struct = (void*)data;
	args->flags_num = NUMBER_OF_FLAGS;
	args->funcs = &(g_funcs[0]);
	args->flags = &(g_flags[0]);
}
