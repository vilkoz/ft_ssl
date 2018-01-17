/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrybalko <vrybalko@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/19 14:41:24 by vrybalko          #+#    #+#             */
/*   Updated: 2017/11/19 18:05:19 by vrybalko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "queue.h"

void			queue_init(t_queue *q, size_t capacity, size_t sz)
{
	if ((q->buffer = malloc(capacity * sz)) == NULL)
		return ;
	q->buffer_end = (char*)q->buffer + capacity * sz;
	q->capacity = capacity;
	q->count = 0;
	q->sz = sz;
	q->head = q->buffer;
	q->tail = q->buffer;
}

void			queue_free(t_queue *q)
{
	ft_memdel(q->buffer);
}

void			queue_push(t_queue *q, void *item)
{
	if (q->count == q->capacity)
		ft_putendl_fd("WARNING QUEUE IS OVERFLOWED SOME DATA MAY BE LOST", 2);
	ft_memcpy(q->head, item, q->sz);
	q->head = (char*)q->head + q->sz;
	if (q->head == q->buffer_end)
		q->head = q->buffer;
	q->count++;
}

void			*queue_pop(t_queue *q)
{
	void		*item;

	if (q->count == 0)
		return (NULL);
	item = ft_memalloc(q->sz);
	ft_memcpy(item, q->tail, q->sz);
	q->tail = (char*)q->tail + q->sz;
	if (q->tail == q->buffer_end)
		q->tail = q->buffer;
	q->count--;
	return (item);
}
