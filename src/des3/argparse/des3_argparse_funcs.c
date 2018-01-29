/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3_argparse_funcs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 17:00:36 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/29 18:08:10 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des3_argparse_private.h"
#include "libft.h"

int	des3_cbc_argparse_set_iv(int ac, char **av, void *data, int j)
{
	int		ret;

	if (j + 1 >= ac)
	{
		ft_putendl_fd("ft_ssl: des: no key after -iv", 2);
		return (-1);
	}
	if ((ret = convert_hex_key(&(((t_des3_config*)data)->iv[0]),
					&(av[j + 1][0]))) < 0)
	{
		ft_putstr_fd("ft_ssl: des: wrong hex char in iv: ", 2);
		ft_putchar_fd((char)-ret, 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	((t_des3_config*)data)->iv_status = 1;
	return (0);
}

int	des3_argparse_set_keyarg(int ac, char **av, void *data, int j)
{
	int		ret;
	int		i;
	char	tmp[48];

	if (j + 1 >= ac)
	{
		ft_putendl_fd("ft_ssl: des: no key after -k", 2);
		return (-1);
	}
	ft_memset((void*)&(tmp[0]), '0', 48);
	ft_memcpy((void*)&(tmp[0]), (void*)av[j + 1],
			MIN(ft_strlen(av[j + 1]), 48));
	i = -1;
	while (++i < 3)
	{
		if ((ret = convert_hex_key(&(((t_des3_config*)data)->key[i * 16]),
						&(tmp[i * 16]))) < 0)
		{
			ft_putstr_fd("ft_ssl: des: wrong hex char in key: ", 2);
			ft_putchar_fd((char)-ret, 2);
			ft_putchar_fd('\n', 2);
			return (-1);
		}
	}
	((t_des3_config*)data)->key_mode = KEY_ARG;
	return (0);
}
