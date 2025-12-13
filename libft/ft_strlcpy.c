#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	lenght;

	lenght = ft_strlen(src);
	if (size != 0)
	{
		while (size - 1 && *src != '\0')
		{
			*dst = *src;
			dst++;
			src++;
			size--;
		}
		*dst = '\0';
	}
	return (lenght);
}
