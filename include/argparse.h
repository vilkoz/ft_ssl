/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argparse.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 13:14:59 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/18 20:02:56 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGPARSE_H
# define ARGPARSE_H

# include "base64.h"

# ifndef NULL
#  define NULL (void*)0
# endif

typedef struct		s_args
{
	void			(*parse_func)(int ac, char **av, void **data_struct);
	void			(*run_func)(void *data_struct);
	void			*data_struct;
}					t_args;

enum				e_program
{
	BASE64,
	DES_ECB,
	DES_CBC,
	NUMBER_OF_PROGRAMS
};

static char		*g_a[NUMBER_OF_PROGRAMS + 1] = {
					"base64", "des", "des-cbc", NULL};
static void		(*g_f[NUMBER_OF_PROGRAMS])(int, char **, void **) = {
					base64_argparse, NULL, NULL};
static void		(*g_r[NUMBER_OF_PROGRAMS])(void *) = {
					base64_run, NULL, NULL};

#endif
