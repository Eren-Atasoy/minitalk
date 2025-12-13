#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d_str;
	const char	*s_str;

	d_str = (char *)dest;
	s_str = (const char *)src;
	if (d_str < s_str)
	{
		while (n)
		{
			*d_str = *s_str;
			d_str++;
			s_str++;
			n--;
		}
	}
	if (d_str > s_str)
	{
		while (n)
		{
			n--;
			d_str[n] = s_str[n];
		}
	}
	return (dest);
}
