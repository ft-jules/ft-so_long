/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 18:51:03 by jules             #+#    #+#             */
/*   Updated: 2024/04/05 18:51:05 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp_node;

	if (!lst || !(*lst) || !del)
		return ;
	while ((*lst))
	{
		temp_node = (*lst)->next;
		ft_lstdelone(*lst, del);
		(*lst) = temp_node;
	}
	lst = NULL;
}
