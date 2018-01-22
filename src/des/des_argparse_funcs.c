/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_argparse_funcs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 00:13:36 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/22 23:17:00 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des_argparse_private.h"
#include "libft.h"

int	des_argparse_set_decode(int ac, char **av, t_des_config *data, int j)
{
	(void)ac;
	(void)av;
	(void)j;
	data->mode = DECRYPT_FLAG;
	return (0);
}

int	des_argparse_set_filein(int ac, char **av, t_des_config *data, int j)
{
	if (j + 1 >= ac)
	{
		ft_putendl_fd("ft_ssl: des: no file name after -i", 2);
		return (-1);
	}
	data->in_mode = FILEIN;
	data->in_fd = open(av[j + 1], O_RDONLY);
	if (data->in_fd == -1)
	{
		perror("ft_ssl: des");
		return (-1);
	}
	return (0);
}

int	des_argparse_set_fileout(int ac, char **av, t_des_config *data, int j)
{
	if (j + 1 >= ac)
	{
		ft_putendl_fd("ft_ssl: des: no file name after -o", 2);
		return (-1);
	}
	data->out_mode = FILEOUT;
	data->out_fd = open(av[j + 1], O_WRONLY | O_CREAT, 0664);
	if (data->in_fd == -1)
	{
		perror("ft_ssl: des");
		return (-1);
	}
	return (0);
}

int	des_argparse_set_b64(int ac, char **av, t_des_config *data, int j)
{
	(void)ac;
	(void)av;
	(void)j;
	data->b64_mode = BASE64;
	return (0);
}

int	des_argparse_set_keyarg(int ac, char **av, t_des_config *data, int j)
{
	int		ret;

	if (j + 1 >= ac)
	{
		ft_putendl_fd("ft_ssl: des: no key after -k", 2);
		return (-1);
	}
	if ((ret = convert_hex_key(&(data->key[0]), &(av[j + 1][0]))) < 0)
	{
		ft_putstr_fd("ft_ssl: des: wrong hex char in key: ", 2);
		ft_putchar_fd((char)-ret, 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	data->key_mode = KEY_ARG;
	return (0);
}
