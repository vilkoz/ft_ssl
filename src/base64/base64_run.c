/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 13:43:29 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/27 16:03:30 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64_argparse_private.h"
#include "libft.h"
#include "base64.h"
#include "reader.h"

static void				base64_output(t_base64_config *data, char *out,
							size_t len)
{
	if (data->mode == ENCODE)
		ft_putstr_fd(out, data->out_fd);
	else
		write(data->out_fd, out, len);
}

void					base64_run(void *data_struct)
{
	t_base64_config		*data;
	unsigned char		*in;
	char				*out;
	size_t				sum_len;

	data = (t_base64_config*)data_struct;
	if ((in = reader(data->in_fd, &sum_len)) == NULL)
		out = ft_strdup("");
	else
		out = data->mode == ENCODE ? base64_encode(in, sum_len) :
			base64_decode((char*)in, &sum_len);
	base64_output(data, out, sum_len);
	if (data->in_mode == FILEIN)
		close(data->in_fd);
	if (data->out_mode == FILEOUT)
		close(data->out_fd);
	ft_memdel((void**)&out);
	ft_memdel((void**)&data);
}
