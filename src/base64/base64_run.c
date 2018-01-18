/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 13:43:29 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/18 18:12:28 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64_argparse_private.h"
#include "libft.h"
#include "base64.h"

#define B64_BUF 24

static char		*reader(int fd)
{
	t_list			*list;
	t_list			*tmp;
	unsigned char	buf[B64_BUF];
	char			*out;

	list = NULL;
	ft_bzero((void*)&buf[0], B64_BUF);
	while (read(fd, buf, B64_BUF) > 0)
	{
		ft_lstadd(&list, ft_lstnew((void*)buf, B64_BUF + 1));
		ft_bzero((void*)&buf[0], B64_BUF);
	}
	if (ft_lst_size(list) == 0)
		return (NULL);
	out = ft_strnew(ft_lst_size(list) * B64_BUF);
	list = ft_lst_rev(list);
	tmp = list;
	while (tmp)
	{
		out = ft_strncat(out, (char*)tmp->content,
				ft_strlen((char*)tmp->content));
		tmp = tmp->next;
	}
	ft_lstdel(&list, NULL);
	return (out);
}

void			base64_run(void *data_struct)
{
	t_base64_config		*data;
	char				*in;
	char				*out;

	data = (t_base64_config*)data_struct;
	if ((in = reader(data->in_fd)) == NULL)
		out = ft_strdup("");
	else
		out = ENCODE ? base64_encode(in) : base64_decode(in);
	ft_putstr_fd(out, data->out_fd);
	ft_memdel((void**)&out);
	ft_memdel((void**)&in);
	if (data->in_mode == FILEIN)
		close(data->in_fd);
	if (data->out_mode == FILEOUT)
		close(data->out_fd);
}
