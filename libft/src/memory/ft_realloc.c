#include "libft.h"

void	*ft_realloc(void *buf, size_t old_size, size_t size)
{
	void	*new_buf;

	new_buf = ft_memalloc(size);
	if (buf != NULL && old_size != 0)
	{
		new_buf = ft_memcpy(new_buf, buf, old_size);
		free(buf);
	}
	return (new_buf);
}
