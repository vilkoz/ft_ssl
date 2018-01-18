/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_rev.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/18 17:37:50 by vrybalko          #+#    #+#             */
/*   Updated: 2018/01/18 17:49:32 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lst_rev(t_list *list)
{
	t_list		*prev;
	t_list		*next;

	if (list == NULL)
		return (NULL);
	prev = NULL;
	while (list)
	{
		next = list->next;
		list->next = prev;
		prev = list;
		list = next;
	}
	return (prev);
}
