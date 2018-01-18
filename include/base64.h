/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 23:11:51 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/18 20:41:34 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE64_H
# define BASE64_H

# include <stddef.h>

/*
** base64_encode encodes bytesteam @in in base64
** returns allocated on heap null-terminated string
*/

char			*base64_encode(unsigned char *in, size_t len);

/*
** base64_decode decodes base64 string @in
** returns allocated on heap null-terminated string
*/

char			*base64_decode(char *in);

void			base64_argparse(int ac, char **av, void **data_struct);

void			base64_run(void *data_struct);

#endif
