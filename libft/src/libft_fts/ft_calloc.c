/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 18:50:14 by jules             #+#    #+#             */
/*   Updated: 2024/04/05 18:50:16 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	total;
	void	*calloc;

	total = count * size;
	if (size != 0 && count > (size_t)-1 / size)
		return (NULL);
	calloc = (void *)malloc(total);
	if (calloc == NULL)
		return (NULL);
	ft_bzero(calloc, total);
	return ((void *)calloc);
}
