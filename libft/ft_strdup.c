/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eratasoy <eratasoy@student.42istanbul      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:04:06 by eratasoy          #+#    #+#             */
/*   Updated: 2025/07/10 11:04:09 by eratasoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
