/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eratasoy <eratasoy@student.42istanbul      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:03:04 by eratasoy          #+#    #+#             */
/*   Updated: 2025/07/10 11:03:08 by eratasoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (*little == '\0')
	{
		return ((char *)big);
	}
	while (*big && len)
	{
		i = 0;
		while (big[i] == little[i] && little[i] && big[i] && i < len)
		{
			i++;
		}
		if (little[i] == '\0')
		{
			return ((char *)(big));
		}
		big++;
		len--;
	}
	return (NULL);
}
