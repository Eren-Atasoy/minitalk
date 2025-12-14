/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eratasoy <eratasoy@student.42istanbul      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:00:18 by eratasoy          #+#    #+#             */
/*   Updated: 2025/07/10 11:00:19 by eratasoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
