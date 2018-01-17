#include "libft.h"

size_t		ft_lst_size(t_list *head)
{
	size_t		size;
	t_list		*tmp;

	size = 0;
	tmp = head;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}
