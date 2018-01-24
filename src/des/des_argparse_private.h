/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_argparse_private.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 23:38:48 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/25 00:02:30 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES_ARGPARSE_PRIVATE_H
# define DES_ARGPARSE_PRIVATE_H

# ifndef NULL
#  define NULL (void*)0
# endif

# include <stdio.h>
# include <fcntl.h>

enum				e_args_flags
{
	DECRYPT_FLAG,
	ENCRYPT_FLAG,
	STDIN,
	FILEIN,
	STDOUT,
	FILEOUT,
	BASE64,
	NOBASE64,
	KEY_ARG,
	KEY_STDIN,
	NUMBER_OF_FLAGS
};

typedef struct		s_des_config
{
	char			mode;
	char			in_mode;
	char			out_mode;
	int				in_fd;
	int				out_fd;
	char			b64_mode;
	char			key_mode;
	unsigned char	key[8];
	unsigned char	iv[8];
}					t_des_config;

/*
** @dst should be 8bytes long
*/

int					convert_hex_key(unsigned char *dst, const char *src);

#endif
