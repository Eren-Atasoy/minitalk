#include "libft.h"
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));

	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);

	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
