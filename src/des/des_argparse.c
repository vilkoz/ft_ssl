/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_argparse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 23:45:42 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/23 00:38:25 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des_argparse_funcs.h"
#include "libft.h"

char			*g_flags[NUMBER_OF_FLAGS] = {
	"-d",
	"-e",
	NULL,
	"-i",
	NULL,
	"-o",
	"-a",
	NULL,
	"-k",
	NULL
};

int				(*g_funcs[NUMBER_OF_FLAGS])(int,
					char **, t_des_config *, int) = {
	des_argparse_set_decode,
	NULL,
	NULL,
	des_argparse_set_filein,
	NULL,
	des_argparse_set_fileout,
	des_argparse_set_b64,
	NULL,
	des_argparse_set_keyarg,
	NULL
};

static void		parse_loop(int ac, char **av, t_des_config *data)
{
	int			i;
	int			j;

	i = 1;
	while (++i < ac)
	{
		j = -1;
		while (++j < NUMBER_OF_FLAGS)
			if (g_flags[j] && g_funcs[j] && !ft_strcmp(av[i], g_flags[j]))
				if ((g_funcs[j])(ac, av, data, i) < 0)
					exit(1);
	}
}

void			des_argparse(int ac, char **av, void **data_struct)
{
	t_des_config		*data;

	data = (t_des_config*)ft_memalloc(sizeof(t_des_config));
	data->mode = ENCRYPT_FLAG;
	data->in_mode = STDIN;
	data->in_fd = 0;
	data->out_mode = STDOUT;
	data->out_fd = 1;
	data->b64_mode = NOBASE64;
	data->key_mode = KEY_STDIN;
	*data_struct = (void*)data;
	if (ac < 3)
		return ;
	parse_loop(ac, av, data);
}
