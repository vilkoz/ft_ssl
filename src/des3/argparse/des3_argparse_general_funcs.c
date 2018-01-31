/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3_argparse_general_funcs.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 19:32:50 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/31 19:32:51 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des3_argparse_private.h"
#include "libft.h"

int	des3_argparse_set_decode(int ac, char **av, void *data, int *j)
{
	(void)ac;
	(void)av;
	(void)j;
	((t_des3_config*)data)->mode = DECRYPT_FLAG;
	return (0);
}

int	des3_argparse_set_filein(int ac, char **av, void *data, int *j)
{
	if (*j + 1 >= ac)
	{
		ft_putendl_fd("ft_ssl: des3: no file name after -i", 2);
		return (-1);
	}
	((t_des3_config*)data)->in_mode = FILEIN;
	((t_des3_config*)data)->in_fd = open(av[*j + 1], O_RDONLY);
	if (((t_des3_config*)data)->in_fd == -1)
	{
		perror("ft_ssl: des3");
		return (-1);
	}
	(*j)++;
	return (0);
}

int	des3_argparse_set_fileout(int ac, char **av, void *data, int *j)
{
	if (*j + 1 >= ac)
	{
		ft_putendl_fd("ft_ssl: des3: no file name after -o", 2);
		return (-1);
	}
	((t_des3_config*)data)->out_mode = FILEOUT;
	((t_des3_config*)data)->out_fd = open(av[*j + 1],
		O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (((t_des3_config*)data)->in_fd == -1)
	{
		perror("ft_ssl: des3");
		return (-1);
	}
	(*j)++;
	return (0);
}

int	des3_argparse_set_b64(int ac, char **av, void *data, int *j)
{
	(void)ac;
	(void)av;
	(void)j;
	((t_des3_config*)data)->b64_mode = BASE64;
	return (0);
}
