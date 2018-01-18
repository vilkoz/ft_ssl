/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_private.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 23:09:21 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/18 00:08:14 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE64_PRIVATE_H
# define BASE64_PRIVATE_H

# include <stdlib.h>

typedef union		u_convert_word
{
	unsigned int	field;
	unsigned char	byte[4];
}					t_convert_word;

# define CEIL_DIV(a, b) ((a) / (b) + ((a) % (b) ? 1 : 0))
# define M64 "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"
# define BASE64_DICT M64

# define SET_B64_CHAR(f, c, n) (f) |= (((c) & 0x3f) << (6 * (n)))
# define REV_B64_CHAR(b) b[0] ^= b[2]; b[2] ^= b[0]; b[0] ^= b[2]

#endif
