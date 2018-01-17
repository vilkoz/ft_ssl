/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 14:42:03 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/19 15:17:21 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_H
# define QUEUE_H

# include "libft.h"

/*
** ring-buffer queue implementation, based on https://stackoverflow.com/a/827749
** sz - item_size
*/

typedef struct		s_queue
{
	void			*buffer;
	void			*buffer_end;
	size_t			capacity;
	size_t			count;
	size_t			sz;
	void			*head;
	void			*tail;
}					t_queue;


void				queue_init(t_queue *q, size_t capacity, size_t sz);
void				queue_free(t_queue *q);
void				queue_push(t_queue *q, void *item);
void				*queue_pop(t_queue *q);

#endif
