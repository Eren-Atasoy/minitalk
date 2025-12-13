#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	length;
	char	*dub;

	length = ft_strlen(s);
	dub = malloc(length + 1);
	if (!dub)
	{
		return (NULL);
	}
	ft_strlcpy(dub, s, length + 1);
	return (dub);
}
