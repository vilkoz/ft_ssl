/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_cbc_argparse_funcs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 01:31:33 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/26 01:25:21 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des_argparse_private.h"
#include "libft.h"

int	des_cbc_argparse_set_iv(int ac, char **av, void *data, int j)
{
	int		ret;

	if (j + 1 >= ac)
	{
		ft_putendl_fd("ft_ssl: des: no key after -iv", 2);
		return (-1);
	}
	if ((ret = convert_hex_key(&(((t_des_config*)data)->iv[0]),
					&(av[j + 1][0]))) < 0)
	{
		ft_putstr_fd("ft_ssl: des: wrong hex char in iv: ", 2);
		ft_putchar_fd((char)-ret, 2);
		ft_putchar_fd('\n', 2);
		return (-1);
	}
	((t_des_config*)data)->iv_status = 1;
	return (0);
}
