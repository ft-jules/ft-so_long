/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 18:50:48 by jules             #+#    #+#             */
/*   Updated: 2024/04/05 18:50:50 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countsize(long num)
{
	size_t	size;

	size = 0;
	if (num < 0)
	{
		size = 1;
		num = num * -1;
	}
	if (num == 0)
		size = 1;
	else
	{
		while (num > 0)
		{
			num = num / 10;
			size++;
		}
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int		size;
	int		sign;
	char	*itoa;
	long	nb;

	nb = (long)n;
	size = ft_countsize(nb);
	sign = 0;
	if (n < 0)
	{
		sign = 1;
		nb = nb * -1;
	}
	itoa = (char *)malloc(sizeof(char) * (size + 1));
	if (itoa == NULL)
		return (NULL);
	itoa[size] = '\0';
	if (sign)
		itoa[0] = '-';
	while (size > sign)
	{
		itoa[--size] = nb % 10 + 48;
		nb = nb / 10;
	}
	return (itoa);
}
