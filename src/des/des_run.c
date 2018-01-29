/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 01:19:58 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/29 14:07:07 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "des.h"
#include "des_argparse_private.h"
#include "reader.h"
#include "base64.h"

/*
** @dst should be 8bytes long
*/

int		convert_hex_key(unsigned char *dst, const char *src)
{
	unsigned char		arg[16];
	unsigned char		half[9];
	int					tmp;
	int					i;

	if (!dst || !src)
		return (-1);
	i = -1;
	while (src[++i])
		if (!ft_isdigit(src[i]) && !(ft_tolower(src[i]) >= 'a'
					&& ft_tolower(src[i]) <= 'f'))
			return (-src[i]);
	ft_bzero((void*)dst, 8);
	ft_bzero((void*)&(arg[0]), 16);
	ft_strncpy((char*)&(arg[0]), (src), 16);
	ft_bzero((void*)&(half[0]), 9);
	ft_memcpy((void*)&(half[0]), (void*)&(arg[0]), 8);
	tmp = ft_atoi_base((char*)&(half[0]), 16);
	ft_memrcpy((void*)dst, &tmp, 4);
	ft_memcpy((void*)&(half[0]), (void*)&(arg[8]), 8);
	tmp = ft_atoi_base((char*)&(half[0]), 16);
	ft_memrcpy((void*)(dst + 4), &tmp, 4);
	return (0);
}

static void		des_output(t_des_config *data, void *out, size_t len)
{
	t_byte		*b64_encoded;

	if (data->mode == DECRYPT_FLAG)
	{
		if (len % 8 != 0)
			len -= len % 8;
	}
	if (data->b64_mode == BASE64 && data->mode == ENCRYPT_FLAG)
	{
		b64_encoded = (t_byte*)base64_encode((unsigned char*)out, len);
		write(data->out_fd, b64_encoded, ft_strlen((char*)b64_encoded));
		ft_putchar_fd('\n', data->out_fd);
		ft_memdel((void**)&b64_encoded);
		return ;
	}
	if (data->mode == ENCRYPT_FLAG)
		write(data->out_fd, (char*)out, len);
	else
		write(data->out_fd, (char*)out, len - ((unsigned char*)out)[len - 1]);
}

static void		cleanup(t_des_config *data, char *out, unsigned char *in)
{
	if (data->in_mode == FILEIN)
		close(data->in_fd);
	if (data->out_mode == FILEOUT)
		close(data->out_fd);
	ft_memdel((void**)&out);
	ft_memdel((void**)&in);
	ft_memdel((void**)&data);
}

static void		set_pass(t_des_config *data)
{
	char		tmp[17];
	char		*pass;

	ft_bzero((void*)&(tmp[0]), 17);
	pass = getpass("enter pass:");
	ft_strncpy(tmp, pass, 16);
	convert_hex_key(&(data->key[0]), &(tmp[0]));
}

void			add_padd(unsigned char **in, size_t *len)
{
	void				*out;
	unsigned char		padd_size;

	padd_size = 8 - (*len % 8);
	out = (void*)ft_strnew(*len + padd_size);
	ft_memcpy((void*)out, (void*)*in, *len);
	ft_memset((void*)(out + (*len)), padd_size, (size_t)padd_size);
	ft_memdel((void**)in);
	*in = out;
	*len = *len + padd_size;
}

void			des_run(void *arg)
{
	t_des_config	*data;
	unsigned char	*in;
	void			*out;
	size_t			sum_len;

	data = (t_des_config*)arg;
	if (data->chiper_mode == CBC && data->iv_status == 0)
		return ft_putendl_fd("ft_ssl: des-cbc: no -iv provided!", 2);
	out = NULL;
	if (data->key_mode == KEY_STDIN)
		set_pass(data);
	if ((in = reader(data->in_fd, &sum_len)) == NULL)
		return cleanup(data, (char*)out, in);
	if (data->b64_mode == BASE64 && data->mode == DECRYPT_FLAG)
	{
		out = (void*)base64_decode((char*)in, &sum_len);
		ft_memdel((void**)&in);
		in = (unsigned char*)out;
	}
	if (data->mode == ENCRYPT_FLAG)
		add_padd(&in, &sum_len);
	out = (void*)des_process_blocks(BYTE_ARRAY(in, sum_len),
		&(data->key[0]), data->chiper_mode == CBC ? &(data->iv[0]): NULL,
		data->mode == ENCRYPT_FLAG ? ENCRYPT : DECRYPT);
	des_output(data, (t_byte*)out, sum_len);
	cleanup(data, (char*)out, in);
}
