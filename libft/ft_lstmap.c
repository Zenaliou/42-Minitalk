/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niclee <niclee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 11:47:39 by niclee            #+#    #+#             */
/*   Updated: 2024/11/28 11:54:28 by niclee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_elt;

	new_list = NULL;
	while (lst)
	{
		new_elt = ft_lstnew(f(lst->content));
		if (!new_elt)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_elt);
		lst = lst->next;
	}
	return (new_list);
}
