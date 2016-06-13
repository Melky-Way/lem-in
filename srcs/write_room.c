/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoudan <msoudan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/06 17:35:29 by msoudan           #+#    #+#             */
/*   Updated: 2015/11/06 17:35:32 by msoudan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Makes a t_room struct with the name and position of the room.
*/

t_room		*write_room(char *name, char *x, char *y)
{
	t_room	*tmp;

	tmp = NULL;
	if ((tmp = (t_room *)malloc(sizeof(t_room))) != NULL)
	{
		tmp->name = name;
		tmp->x = ft_atoi(x);
		tmp->y = ft_atoi(y);
		tmp->ant = NULL;
		tmp->tubes = NULL;
	}
	else
		free(name);
	return (tmp);
}
