/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_room.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoudan <msoudan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/22 13:10:44 by msoudan           #+#    #+#             */
/*   Updated: 2014/03/22 17:02:10 by msoudan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#define FRST ((char **)tmp->content)[0]
#define SCND ((char **)tmp->content)[1]

static int		count_tubes(char *room, t_room *map, t_list **tubes)
{
	int		tubes_nb;
	t_list	*tmp;

	tubes_nb = 0;
	tmp = (*tubes);
	while (tmp != NULL)
	{
		if (ft_strcmp(FRST, room) == 0 && !wrong_turn(SCND, map))
			tubes_nb++;
		else if (ft_strcmp(SCND, room) == 0 && !wrong_turn(FRST, map))
			tubes_nb++;
		tmp = tmp->next;
	}
	return (tubes_nb);
}

static char		**name_doors(char *room, int nb, t_room *map, t_list **tubes)
{
	char		**names;
	t_list		*tmp;

	names = (char **)malloc(sizeof(char *) * (nb + 1));
	if (names != NULL)
	{
		names[nb] = NULL;
		tmp = (*tubes);
		while (nb != 0 && tmp != NULL)
		{
			if (ft_strcmp(FRST, room) == 0 && !wrong_turn(SCND, map))
				names[--nb] = ft_strdup(SCND);
			else if (ft_strcmp(SCND, room) == 0 && !wrong_turn(FRST, map))
				names[--nb] = ft_strdup(FRST);
			tmp = tmp->next;
		}
	}
	return (names);
}

static t_room	**make_doors(char *room_name, t_list **tubes, t_room *prev,
								t_queen **ant)
{
	int			tub_nb;
	char		**door_names;
	t_room		**doors;

	tub_nb = count_tubes(room_name, prev, tubes);
	door_names = tub_nb ? name_doors(room_name, tub_nb, prev, tubes) : NULL;
	doors = tub_nb ? (t_room **)malloc(sizeof(**doors) * (tub_nb + 1)) : NULL;
	if (doors != NULL)
	{
		doors[tub_nb] = NULL;
		while (--tub_nb >= 0)
			doors[tub_nb] = draw_room(door_names[tub_nb], prev, tubes, ant);
	}
	ft_arrdel(&door_names);
	return (doors);
}

/*
** Recursive function that creates a tree of rooms and links.
*/

t_room			*draw_room(char *name, t_room *prev, t_list **tubes,
							t_queen **ant)
{
	t_room		*new_room;
	static int	path_limit = 0;

	if ((new_room = (t_room *)malloc(sizeof(t_room))) != NULL)
	{
		new_room->name = ft_strdup(name);
		new_room->ant = NULL;
		get_x_y(new_room, name, ant);
		new_room->prev = prev;
		if (ft_strcmp(name, (*ant)->end) == 0 || path_limit > 500)
		{
			new_room->tubes = NULL;
			path_limit++;
		}
		else
			new_room->tubes = make_doors(new_room->name, tubes, new_room, ant);
		return (new_room);
	}
	return (NULL);
}
