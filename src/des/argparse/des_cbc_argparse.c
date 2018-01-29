/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cbc_argparse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 01:25:29 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/25 01:38:12 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des_argparse_funcs.h"
#include "libft.h"
#include "argparse_struct.h"

static char		*g_flags[NUMBER_OF_FLAGS] = {
	"-d",
	"-e",
	NULL,
	"-i",
	NULL,
	"-o",
	"-a",
	NULL,
	"-k",
	NULL,
	"-iv",
	NULL
};

static int		(*g_funcs[NUMBER_OF_FLAGS])(int,
					char **, void *, int) = {
	des_argparse_set_decode,
	NULL,
	NULL,
	des_argparse_set_filein,
	NULL,
	des_argparse_set_fileout,
	des_argparse_set_b64,
	NULL,
	des_argparse_set_keyarg,
	NULL,
	des_cbc_argparse_set_iv,
	NULL
};

void			des_cbc_argparse(int ac, char **av, void **data_struct,
					t_args *args)
{
	t_des_config		*data;

	(void)ac;
	(void)av;
	data = (t_des_config*)ft_memalloc(sizeof(t_des_config));
	data->mode = ENCRYPT_FLAG;
	data->in_mode = STDIN;
	data->in_fd = 0;
	data->out_mode = STDOUT;
	data->out_fd = 1;
	data->b64_mode = NOBASE64;
	data->key_mode = KEY_STDIN;
	data->chiper_mode = CBC;
	data->iv_status = 0;
	*data_struct = (void*)data;
	args->flags_num = NUMBER_OF_FLAGS;
	args->funcs = &(g_funcs[0]);
	args->flags = &(g_flags[0]);
}
