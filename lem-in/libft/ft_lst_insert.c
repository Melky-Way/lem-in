/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoudan <msoudan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/26 14:01:45 by msoudan           #+#    #+#             */
/*   Updated: 2014/05/17 19:10:54 by msoudan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_list_bdy(t_list **list, t_list **tmp, void *data, size_t size)
{
	t_dbl	*new;

	new = (t_dbl*)malloc(sizeof(t_dbl));
	if (new != NULL)
	{
		new->content = (data == NULL) ? NULL : (void*)malloc(size);
		if (data != NULL)
		{
			ft_memcpy(new->content, data, size);
			new->size = (data == NULL) ? 0 : size;
		}
		(*tmp)->next->prev = new;
		(*tmp)->prev->next = new;
		new->prev = (*tmp)->prev;
		new->next = (*tmp);
		(*list)->lenght++;
	}
}

t_list		*ft_list_insert(t_list *list, void *data, int pos, size_t size)
{
	t_list	*temp;
	int		i;

	i = 1;
	if (list != NULL)
	{
		temp = list->head;
		while (temp != NULL && i <= pos)
		{
			if (i == pos)
			{
				if (temp->next == NULL)
					list = ft_dlist_tail(list, data, size);
				else if (temp->prev == NULL)
					list = ft_dlist_head(list, data, size);
				else
					ft_dlist_bdy(&list, &temp, data, size);
			}
			else
				temp = temp->next;
			i++;
		}
	}
	return (list);
}
