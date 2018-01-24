/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_argparse_funcs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 14:22:09 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/24 02:18:47 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64_argparse_private.h"
#include "base64_argparse_funcs.h"
#include "libft.h"

int	base64_argparse_set_decode(int ac, char **av, t_base64_config *data, int j)
{
	(void)ac;
	(void)av;
	(void)j;
	data->mode = DECODE;
	return (0);
}

int	base64_argparse_set_encode(int ac, char **av, t_base64_config *data, int j)
{
	(void)ac;
	(void)av;
	(void)j;
	data->mode = ENCODE;
	return (0);
}

int	base64_argparse_set_filein(int ac, char **av, t_base64_config *data, int j)
{
	if (j + 1 >= ac)
	{
		ft_putendl_fd("ft_ssl: base64: no file name after -i", 2);
		return (-1);
	}
	data->in_mode = FILEIN;
	data->in_fd = open(av[j + 1], O_RDONLY);
	if (data->in_fd == -1)
	{
		perror("ft_ssl: base64");
		return (-1);
	}
	return (0);
}

int	base64_argparse_set_fileout(int ac, char **av, t_base64_config *data, int j)
{
	if (j + 1 >= ac)
	{
		ft_putendl_fd("ft_ssl: base64: no file name after -o", 2);
		return (-1);
	}
	data->out_mode = FILEOUT;
	data->out_fd = open(av[j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (data->in_fd == -1)
	{
		perror("ft_ssl: base64");
		return (-1);
	}
	return (0);
}
