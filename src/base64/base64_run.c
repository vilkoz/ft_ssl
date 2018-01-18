/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_run.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 13:43:29 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/18 21:11:11 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "base64_argparse_private.h"
#include "libft.h"
#include "base64.h"

#define B64_BUF 24

static t_list			*read_loop(int fd, size_t *sum_len)
{
	t_list			*list;
	unsigned char	buf[B64_BUF];
	int				i;

	list = NULL;
	*sum_len = 0;
	ft_bzero((void*)&buf[0], B64_BUF);
	while ((i = read(fd, buf, B64_BUF)) > 0)
	{
		ft_lstadd(&list, ft_lstnew((void*)buf, i + 1));
		ft_bzero((void*)&buf[0], B64_BUF);
		*sum_len += i;
	}
	return (list);
}

static unsigned char	*join_list(t_list *list, size_t *sum_len)
{
	unsigned char		*out;
	size_t				i;
	t_list				*tmp;

	out = (unsigned char*)ft_strnew(*sum_len);
	list = ft_lst_rev(list);
	tmp = list;
	i = 0;
	while (tmp && i < *sum_len)
	{
		(void)ft_memcpy((void*)out + i, tmp->content,
				tmp->content_size - 1);
		i += tmp->content_size - 1;
		tmp = tmp->next;
	}
	return (out);
}

static unsigned char	*reader(int fd, size_t *sum_len)
{
	unsigned char	*out;
	t_list			*list;

	list = read_loop(fd, sum_len);
	if (*sum_len == 0)
		return (NULL);
	out = join_list(list, sum_len);
	ft_lstdel(&list, NULL);
	return (out);
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
			base64_decode((char*)in);
	ft_putstr_fd(out, data->out_fd);
	ft_memdel((void**)&out);
	if (data->in_mode == FILEIN)
		close(data->in_fd);
	if (data->out_mode == FILEOUT)
		close(data->out_fd);
}
