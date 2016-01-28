/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_scouts.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoudan <msoudan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 02:26:46 by msoudan           #+#    #+#             */
/*   Updated: 2014/03/23 03:15:19 by msoudan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_room	*copy_room(t_room *map)
{
	t_room		*copy;

	if (map == NULL)
		return (NULL);
	if ((copy = (t_room *)malloc(sizeof(t_room))) != NULL)
	{
		copy->name = ft_strdup(map->name);
		copy->ant = NULL;
		copy->prev = NULL;
		copy->tubes = NULL;
		copy->x = map->x;
		copy->y = map->y;
	}
	return (copy);
}

/*
** Copies the way to a t_list grouping all possible ways so far.
*/

static t_dlist	*copy_way_on_scroll(t_room **map)
{
	t_room		*tmp;
	t_room		*content;
	t_dlist		*new_way;

	if ((tmp = *map) == NULL)
		return (NULL);
	if ((new_way = ft_dlist_new()) != NULL)
	{
		while (tmp != NULL)
		{
			content = copy_room(tmp);
			ft_dlist_head(new_way, (void *)content, sizeof(t_room*));
			tmp = tmp->prev;
		}
	}
	return (new_way);
}

/*
** Recursively exploring the tree of rooms and doors. If the end of the way is
** the exit, we save that path.
*/

int				send_scouts(t_room **map, t_queen **ant, t_list **scroll)
{
	int			i;

	i = -1;
	if ((*map) != NULL && (*map)->tubes != NULL)
	{
		while ((*map)->tubes[++i] != NULL)
			send_scouts(&(*map)->tubes[i], ant, scroll);
	}
	else if ((*map)->tubes == NULL && !ft_strcmp((*map)->name, (*ant)->end))
		ft_lstpushback(scroll, copy_way_on_scroll(map), sizeof(*map));
	return (0);
}
