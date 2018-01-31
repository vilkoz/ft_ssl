/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 01:19:58 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/31 19:34:29 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "des.h"
#include "argparse/des_argparse_private.h"
#include "reader.h"
#include "base64.h"

static void		des_output(t_des_config *data, void *out, size_t len)
{
	t_byte		*b64_encoded;
	size_t		pad_size;

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
	{
		pad_size = ((unsigned char*)out)[len - 1];
		pad_size < len ? write(data->out_fd, (char*)out, len - pad_size) : 0;
		pad_size >= len ? ft_putendl_fd("./ft_ssl: des: bad decrypt", 2) : 0;
	}
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

static void		set_pass(t_byte *key, const char *prompt)
{
	char		tmp[17];
	char		*pass;
	int			ret;

	ft_memset((void*)&(tmp[0]), '0', 17);
	pass = getpass(prompt);
	ft_strncpy(tmp, pass, 16);
	if ((ret = convert_hex_key(key, &(tmp[0]))) < 0)
	{
		ft_putstr_fd("ft_ssl: des: wrong hex char in key: ", 2);
		ft_putchar_fd((char)-ret, 2);
		ft_putchar_fd('\n', 2);
		exit(1);
	}
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
	out = NULL;
	if (data->key_mode == KEY_STDIN)
		set_pass(&(data->key[0]), "enter key in hex: ");
	if (data->iv_status == 0 && data->chiper_mode == CBC)
		set_pass(&(data->iv[0]), "enter iv in hex: ");
	if ((in = reader(data->in_fd, &sum_len)) == NULL && data->mode == DECRYPT)
		return (cleanup(data, (char*)out, in));
	if (data->b64_mode == BASE64 && data->mode == DECRYPT_FLAG)
	{
		out = (void*)base64_decode((char*)in, &sum_len);
		ft_memdel((void**)&in);
		in = (unsigned char*)out;
	}
	(data->mode == ENCRYPT_FLAG) ? add_padd(&in, &sum_len) : 0;
	out = (void*)des_process_blocks(BYTE_ARRAY(in, sum_len),
		&(data->key[0]), data->chiper_mode == CBC ? &(data->iv[0]) : NULL,
		data->mode == ENCRYPT_FLAG ? ENCRYPT : DECRYPT);
	des_output(data, (t_byte*)out, sum_len);
	cleanup(data, (char*)out, in);
}
