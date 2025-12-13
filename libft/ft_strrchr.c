#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	length;

	length = ft_strlen(s);
	if ((unsigned char)c == '\0')
	{
		return ((char *)(s + length));
	}
	while (length--)
	{
		if ((unsigned char)s[length] == (unsigned char)c)
		{
			return ((char *)(s + length));
		}
	}
	return (NULL);
}
