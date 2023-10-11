/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 15:13:39 by lyeh              #+#    #+#             */
/*   Updated: 2023/09/10 15:27:42 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp_node;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		tmp_node = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tmp_node;
	}
	lst = NULL;
}
