/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_argparse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 13:06:43 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/18 16:32:53 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64_argparse_private.h"
#include "libft.h"

char			*g_flags[NUMBER_OF_FLAGS] = {
	"-d",
	"-e",
	NULL,
	"-i",
	NULL,
	"-o"
};

int				(*g_funcs[NUMBER_OF_FLAGS])(int,
					char **, t_base64_config *, int) = {
	base64_argparse_set_decode,
	base64_argparse_set_encode,
	NULL,
	base64_argparse_set_filein,
	NULL,
	base64_argparse_set_fileout
};

static void		parse_loop(int ac, char **av, t_base64_config *data)
{
	int			i;
	int			j;

	i = 1;
	while (++i < ac)
	{
		j = -1;
		while (++j < NUMBER_OF_FLAGS)
			if (g_flags[j] && !ft_strcmp(av[i], g_flags[j]))
				if ((g_funcs[j])(ac, av, data, i) < 0)
					exit(1);
	}
}

void			base64_argparse(int ac, char **av, void **data_struct)
{
	t_base64_config		*data;

	data = (t_base64_config*)ft_memalloc(sizeof(t_base64_config));
	data->mode = ENCODE;
	data->in_mode = STDIN;
	data->in_fd = 0;
	data->out_mode = STDOUT;
	data->out_fd = 1;
	*data_struct = (void*)data;
	if (ac < 3)
		return ;
	parse_loop(ac, av, data);
}
