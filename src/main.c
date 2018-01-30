/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 12:35:49 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/31 01:44:53 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "argparse.h"

/*
** TODO:
** [x] sleep
** [x] des-cbc read iv from input
** [-] des3 display iv in getpass
** [+] des3-ecb mode
** [+] progams list
** [+] invalid argument message
** [+] help message for each program
** [ ] fix segfault if pass EOF to getpass
*/

static char			*g_a[NUMBER_OF_PROGRAMS + 1] = {"base64",
	"des", "des-ecb", "des-cbc", "des3", "des3-ecb", "des3-cbc", NULL};
static void			(*g_f[NUMBER_OF_PROGRAMS])(int, char **, void **,
						t_args *args) = {base64_argparse,
	des_argparse, des_argparse, des_cbc_argparse, des3_argparse,
	des3_ecb_argparse, des3_argparse};
static void			(*g_r[NUMBER_OF_PROGRAMS])(void *) = {base64_run,
	des_run, des_run, des_run, des3_run, des3_run, des3_run};
static void			(*g_h[NUMBER_OF_PROGRAMS])(void) = {base64_help,
	des_help, des_help, des_cbc_help, des3_help, des3_ecb_help, des3_help};
static char			*g_help[] = {"usage ./ft_ssl <program_name> [program_args]",
	"ft_ssl help:",
	"",
	"Standard commands:",
	"",
	"Mesage Digest commands:",
	"",
	"Chiper commands:",
	"base64",
	"des",
	"des-ecb",
	"des-cbc",
	"des3",
	"des3-ecb",
	"des3-cbc",
	NULL};

void				argparse(int ac, char **av, t_args *args_struct)
{
	int				i;

	if (ac < 2)
	{
		ft_putendl_fd(g_help[0], 2);
		exit(1);
	}
	i = -1;
	while (g_a[++i])
	{
		if (ft_strcmp(av[1], g_a[i]) == 0)
		{
			args_struct->parse_func = g_f[i];
			args_struct->run_func = g_r[i];
			args_struct->program = i;
			break ;
		}
	}
	if (args_struct->parse_func == NULL || args_struct->run_func == NULL)
	{
		i = -1;
		while (g_help[++i])
			ft_putendl_fd(g_help[i], 2);
		exit(1);
	}
}

static void			print_invalid_arg_message(const char *name, const char *arg)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin("./ft_ssl: ", name);
	tmp2 = ft_strjoin(tmp, ": invalid argument: ");
	ft_memdel((void**)&tmp);
	ft_putstr_fd(tmp2, 2);
	ft_putendl_fd(arg, 2);
	ft_memdel((void**)&tmp2);
}

static void			parse_loop(int ac, char **av, void *data, t_args *args)
{
	int			i;
	int			j;
	int			ret;

	i = 1;
	while (++i < ac)
	{
		j = -1;
		ret = -1;
		while (++j < args->flags_num)
			if (args->flags[j] && args->funcs[j]
					&& !ft_strcmp(av[i], args->flags[j]))
			{
				if ((ret = (args->funcs[j])(ac, av, data, &i)) < 0)
					exit(1);
				else
					break ;
			}
		if (ret < 0)
		{
			print_invalid_arg_message(av[1], av[i]);
			g_h[args->program]();
			exit(1);
		}
	}
}

int					main(int ac, char **av)
{
	t_args		args_struct;

	ft_bzero((void*)&args_struct, sizeof(t_args));
	argparse(ac, av, &args_struct);
	args_struct.parse_func(ac, av, &(args_struct.data_struct), &args_struct);
	parse_loop(ac, av, args_struct.data_struct, &args_struct);
	args_struct.run_func(args_struct.data_struct);
	return (0);
}
