/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:12:29 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/18 17:09:47 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	del_func(void *data, size_t size)
{
	(void)size;
	ft_memdel(&data);
}

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list		*tmp;
	t_list		*cur;

	if (del == NULL)
		del = del_func;
	tmp = *alst;
	cur = tmp;
	while (tmp)
	{
		tmp = tmp->next;
		del(cur->content, cur->content_size);
		free(cur);
		cur = tmp;
	}
	*alst = NULL;
}
