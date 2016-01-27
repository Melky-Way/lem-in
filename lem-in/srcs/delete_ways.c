/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_ways.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoudan <msoudan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/10 19:26:38 by msoudan           #+#    #+#             */
/*   Updated: 2015/11/10 19:26:42 by msoudan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		erase_room(t_room **map)
{
	if ((*map) != NULL)
	{
		if ((*map)->name != NULL)
			free((*map)->name);
		if ((*map)->ant != NULL)
			free((*map)->ant);
		if ((*map)->tubes != NULL)
			free((*map)->tubes);
		(*map)->tubes = NULL;
		(*map)->prev = NULL;
		(*map)->name = NULL;
		(*map)->ant = NULL;
		free((*map));
		(*map) = NULL;
	}
}

void		delete_content_dlist(t_dbl *element)
{
	if (element != NULL && element->content != NULL)
	{
		erase_room((t_room **)&(element->content));
		element->content = NULL;
	}
}

void		delete_content_list(t_list *element)
{
	if (element != NULL && element->content != NULL)
	{
		erase_room((t_room **)&(element->content));
		element->content = NULL;
	}
}

static void	delete_iter(t_list *list)
{
	t_list	*tmp;
	t_dlist	*del;
	void	(*func1)(t_dbl *);

	func1 = delete_content_dlist;
	if ((tmp = list) != NULL)
	{
		del = ((t_dlist *)tmp->content);
		ft_dlist_iter(del, func1);
		ft_dlist_del(&del);
		tmp->content = NULL;
	}
}

void		delete_ways(t_list *list)
{
	void	(*func)(t_list *);

	func = delete_iter;
	if (list != NULL)
	{
		ft_lstiter(list, func);
		ft_lstclear(&list);
	}
}
