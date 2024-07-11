/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 18:47:27 by jules             #+#    #+#             */
/*   Updated: 2024/04/05 18:47:29 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// ft_count_width is in the string file

void	ft_print_char(t_print *format)
{
	unsigned char	c;
	int				k;

	k = ft_count_width(format, 1);
	c = va_arg(format->args, int);
	if (format->dash)
	{
		ft_putchar(format, c);
		ft_space(format, k);
	}
	else
	{
		ft_space(format, k);
		ft_putchar(format, c);
	}
}
