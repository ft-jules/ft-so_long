/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 18:53:19 by jules             #+#    #+#             */
/*   Updated: 2024/04/05 18:53:20 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *need, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!need[i])
		return ((char *)hay);
	if (len == 0)
		return (NULL);
	while (hay[i] && i < len)
	{
		j = 0;
		while ((j + i) < len && need[j] == hay[i + j] && hay[i])
		{
			if (!need[j + 1])
				return ((char *)hay + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
