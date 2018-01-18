/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 12:35:49 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/18 13:40:01 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "argparse.h"

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

int		main(int ac, char **av)
{
	t_args		args_struct;

	ft_bzero((void*)&args_struct, sizeof(t_args));
	argparse(ac, av, &args_struct);
	args_struct.parse_func(ac, av, &args_struct.data_struct);
	args_struct.run_func(args_struct.data_struct);
	return (0);
}
