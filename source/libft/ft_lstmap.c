/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lyeh <lyeh@student.42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 15:27:08 by lyeh              #+#    #+#             */
/*   Updated: 2023/09/11 16:28:07 by lyeh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*node;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	ret = NULL;
	while (lst)
	{
		content = f(lst->content);
		node = ft_lstnew(content);
		if (!node)
		{
			ft_lstclear(&ret, del);
			free(content);
			return (NULL);
		}
		ft_lstadd_back(&ret, node);
		lst = lst->next;
	}
	return (ret);
}
