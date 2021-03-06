/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argparse.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 13:14:59 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/31 00:02:08 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGPARSE_H
# define ARGPARSE_H

# include "base64.h"
# include "des.h"
# include "des3.h"
# include "argparse_struct.h"

# ifndef NULL
#  define NULL (void*)0
# endif

enum				e_program
{
	BASE64,
	DES,
	DES_ECB,
	DES_CBC,
	DES3,
	DES3_ECB,
	DES3_CBC,
	NUMBER_OF_PROGRAMS
};

#endif
