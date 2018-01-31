/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3_argparse_private.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 16:55:42 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/31 17:38:30 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DES3_ARGPARSE_PRIVATE_H
# define DES3_ARGPARSE_PRIVATE_H

# ifndef NULL
#  define NULL (void*)0
# endif

# include <stdio.h>
# include <fcntl.h> 
# define MIN(a, b) ((a) < (b) ? (a) : (b))

enum				e_args_flags
{
	ENCRYPT_FLAG,
	DECRYPT_FLAG,
	STDIN,
	FILEIN,
	STDOUT,
	FILEOUT,
	BASE64,
	NOBASE64,
	KEY_ARG,
	KEY_STDIN,
	IV,
	CBC,
	ECB,
	NUMBER_OF_FLAGS
};

typedef struct		s_des3_config
{
	char			mode;
	char			in_mode;
	char			out_mode;
	int				in_fd;
	int				out_fd;
	char			b64_mode;
	char			key_mode;
	unsigned char	key[25];
	int				iv_status;
	unsigned char	iv[8];
	int				chiper_mode;
}					t_des3_config;

/*
** @dst should be 8bytes long
*/

int					convert_hex_key(unsigned char *dst, const char *src);

void				add_padd(unsigned char **in, size_t *len);

#endif
