#include "libft.h"

void	**ft_lst_to_array(t_list *head)
{
	size_t		size;
	void		**array;
	t_list		*tmp;
	size_t		i;

	size = ft_lst_size(head);
	array = (void**)malloc(sizeof(void*) * (size + 1));
	tmp = head;
	i = 0;
	while (tmp)
	{
		array[i] = ft_memalloc(tmp->content_size);
		ft_memcpy(array[i], tmp->content, tmp->content_size);
		i++;
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}
