/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 17:14:54 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/30 23:39:09 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "argparse/des3_argparse_private.h"
#include "des3.h"
#include "reader.h"
#include "base64.h"

static void		set_pass(t_byte *key, const char *prompt)
{
	char		tmp[48];
	char		*pass;
	int			ret;
	int			i;

	ft_memset((void*)&(tmp[0]), '0', 48);
	pass = getpass(prompt);
	ft_memcpy((void*)&(tmp[0]), (void*)pass, MIN(ft_strlen(pass), 48));
	i = -1;
	while (++i < 3)
	{
		if ((ret = convert_hex_key(&(key[i * 8]), &(tmp[i * 16]))) < 0)
		{
			ft_putstr_fd("ft_ssl: des: wrong hex char: ", 2);
			ft_putchar_fd((char)-ret, 2);
			ft_putchar_fd('\n', 2);
			exit(1);
		}
	}
}

static void		des_output(t_des3_config *data, void *out, size_t len)
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

static void		cleanup(t_des3_config *data, char *out, unsigned char *in)
{
	if (data->in_mode == FILEIN)
		close(data->in_fd);
	if (data->out_mode == FILEOUT)
		close(data->out_fd);
	ft_memdel((void**)&out);
	ft_memdel((void**)&in);
	ft_memdel((void**)&data);
}

void			des3_run(void *arg)
{
	t_des3_config	*data;
	unsigned char	*in;
	void			*out;
	size_t			sum_len;

	data = (t_des3_config*)arg;
	if (data->iv_status == 0)
		set_pass(&(data->iv[0]), "enter iv in hex: ");
	out = NULL;
	if (data->key_mode == KEY_STDIN)
		set_pass(&(data->key[0]), "enter key in hex: ");
	if ((in = reader(data->in_fd, &sum_len)) == NULL && data->mode == DECRYPT)
		return (cleanup(data, (char*)out, in));
	if (data->b64_mode == BASE64 && data->mode == DECRYPT_FLAG)
	{
		out = (void*)base64_decode((char*)in, &sum_len);
		ft_memdel((void**)&in);
		in = (unsigned char*)out;
	}
	(data->mode == ENCRYPT_FLAG) ? add_padd(&in, &sum_len) : 0;
	out = (void*)des3_process_blocks(BYTE_ARRAY(in, sum_len), &(data->key[0]),
		&(data->iv[0]), data->mode);
	des_output(data, (t_byte*)out, sum_len);
	cleanup(data, (char*)out, in);
}
