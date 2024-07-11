/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 18:52:54 by jules             #+#    #+#             */
/*   Updated: 2024/04/05 18:52:56 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	l_src;
	size_t	l_dest;

	l_dest = 0;
	while (l_dest < size && dst[l_dest] != '\0')
		l_dest++;
	l_src = ft_strlen(src);
	i = l_dest;
	j = 0;
	if (l_dest >= size)
		return (size + l_src);
	else
	{
		while (src[j] && i < size - 1)
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		dst[i] = '\0';
	}
	return (l_dest + l_src);
}
