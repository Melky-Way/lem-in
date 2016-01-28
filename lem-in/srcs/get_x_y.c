/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_x_y.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoudan <msoudan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/10 11:11:18 by msoudan           #+#    #+#             */
/*   Updated: 2015/11/10 11:11:22 by msoudan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		get_x_y(t_room *new_room, char *name, t_queen **ant)
{
	t_list	*tmp;

	if (*ant != NULL && (tmp = (*ant)->rooms) != NULL)
	{
		while (ft_strcmp(name, ((t_room *)tmp->content)->name))
			tmp = tmp->next;
		if (tmp != NULL)
		{
			new_room->x = ((t_room *)tmp->content)->x;
			new_room->y = ((t_room *)tmp->content)->y;
		}
	}
}
