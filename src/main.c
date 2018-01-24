/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 12:35:49 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/25 01:40:38 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "argparse.h"

static char			*g_a[NUMBER_OF_PROGRAMS + 1] = {
						"base64", "des", "des-ecb", "des-cbc", NULL};
static void			(*g_f[NUMBER_OF_PROGRAMS])(int, char **, void **,
						t_args *args) = {
						base64_argparse, des_argparse, des_argparse,
						des_cbc_argparse};
static void			(*g_r[NUMBER_OF_PROGRAMS])(void *) = {
						base64_run, des_run, des_run, des_run};

void	argparse(int ac, char **av, t_args *args_struct)
{
	int				i;

	if (ac < 2)
	{
		ft_putendl_fd("usage ./ft_ssl <program_name> [program_args]", 2);
		exit(1);
	}
	i = -1;
	while (g_a[++i])
	{
		if (ft_strcmp(av[1], g_a[i]) == 0)
		{
			args_struct->parse_func = g_f[i];
			args_struct->run_func = g_r[i];
			break ;
		}
	}
	if (args_struct->parse_func == NULL || args_struct->run_func == NULL)
	{
		ft_putendl_fd("usage ./ft_ssl <program_name> [program_args]", 2);
		exit(1);
	}
}

static void		parse_loop(int ac, char **av, void *data, t_args *args)
{
	int			i;
	int			j;

	i = 1;
	while (++i < ac)
	{
		j = -1;
		while (++j < args->flags_num)
			if (args->flags[j] && args->funcs[j]
					&& !ft_strcmp(av[i], args->flags[j]))
				if ((args->funcs[j])(ac, av, data, i) < 0)
					exit(1);
	}
}

int		main(int ac, char **av)
{
	t_args		args_struct;

	ft_bzero((void*)&args_struct, sizeof(t_args));
	argparse(ac, av, &args_struct);
	args_struct.parse_func(ac, av, &(args_struct.data_struct), &args_struct);
	parse_loop(ac, av, args_struct.data_struct, &args_struct);
	args_struct.run_func(args_struct.data_struct);
	return (0);
}
