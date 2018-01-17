/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 23:11:51 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/18 00:23:37 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE64_H
# define BASE64_H

/*
** base64_encode encodes bytesteam @in in base64
** returns allocated on heap null-terminated string
*/

char			*base64_encode(char *in);

/*
** base64_decode decodes base64 string @in 
** returns allocated on heap null-terminated string
*/

char			*base64_decode(char *in);

#endif
