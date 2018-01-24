/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argparse_struct.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 00:48:27 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/25 00:54:15 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGPARSE_STUCT_H
# define ARGPARSE_STUCT_H

typedef struct		s_args
{
	void			(*parse_func)(int ac, char **av, void **data_struct,
						struct s_args *);
	void			(*run_func)(void *data_struct);
	void			*data_struct;
	int				flags_num;
	int				(**funcs)(int, char **, void *, int);
	char			**flags;

}					t_args;

#endif
