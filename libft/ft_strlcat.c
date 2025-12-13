#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_length;
	size_t	src_length;
	size_t	counter;
	size_t	i;

	i = 0;
	dst_length = ft_strlen(dst);
	counter = dst_length;
	src_length = ft_strlen(src);
	if (size <= dst_length)
	{
		return (size + src_length);
	}
	while (counter < size - 1 && src[i] != '\0')
	{
		dst[counter] = src[i];
		counter++;
		i++;
	}
	dst[counter] = '\0';
	return (dst_length + src_length);
}
