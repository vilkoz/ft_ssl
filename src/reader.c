/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 21:03:14 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/29 12:33:00 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "reader.h"

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

static unsigned char	*join_list(t_list **list, size_t *sum_len)
{
	unsigned char		*out;
	size_t				i;
	t_list				*tmp;

	out = (unsigned char*)ft_strnew(*sum_len);
	*list = ft_lst_rev(*list);
	tmp = *list;
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

unsigned char			*reader(int fd, size_t *sum_len)
{
	unsigned char	*out;
	t_list			*list;

	list = read_loop(fd, sum_len);
	if (*sum_len == 0)
		return (NULL);
	out = join_list(&list, sum_len);
	ft_lstdel(&list, NULL);
	return (out);
}
