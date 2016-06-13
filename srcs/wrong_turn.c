/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrong_turn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoudan <msoudan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 00:47:27 by msoudan           #+#    #+#             */
/*   Updated: 2014/03/23 02:11:40 by msoudan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** That function check if that room is already there in the map.
*/

int			wrong_turn(char *name, t_room *map)
{
	t_room	*tmp;

	tmp = map;
	while (tmp != NULL)
	{
		if (ft_strcmp(name, tmp->name) == 0)
			return (1);
		tmp = tmp->prev;
	}
	return (0);
}
