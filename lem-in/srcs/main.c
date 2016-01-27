/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoudan <msoudan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/21 17:46:33 by msoudan           #+#    #+#             */
/*   Updated: 2014/03/22 18:25:44 by msoudan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <unistd.h>

/*
** Checks if there's a start, an end, if there're ants, rooms and tunnels, and
** if start and end are not the same.
*/

static int		ft_check_map_data(t_queen **ant, t_list **tube)
{
	if ((*ant)->ants_nb <= 0 || (*ant)->start == NULL || (*ant)->end == NULL)
		return (0);
	if (!ft_strcmp((*ant)->start, (*ant)->end))
		return (0);
	if ((*ant)->rooms == NULL || (*tube) == NULL)
		return (0);
	return (1);
}

static void		destroy_queen(t_queen **ant)
{
	void		(*func1)(t_list *);

	func1 = delete_content_list;
	if ((*ant)->rooms != NULL)
	{
		ft_lstiter((*ant)->rooms, func1);
		ft_lstclear(&(*ant)->rooms);
	}
	(*ant)->rooms = NULL;
	if ((*ant)->start != NULL)
		free((*ant)->start);
	if ((*ant)->end != NULL)
		free((*ant)->end);
	(*ant)->start = NULL;
	(*ant)->end = NULL;
	free((*ant));
	(*ant) = NULL;
}

static t_queen	*wake_queen_ant(void)
{
	t_queen		*ant;
	t_architect	*bob;

	ant = (t_queen *)malloc(sizeof(t_queen));
	bob = (t_architect *)malloc(sizeof(t_architect));
	if (ant != NULL && bob != NULL)
	{
		ant->start = NULL;
		ant->end = NULL;
		ant->ants_nb = 0;
		ant->rooms = NULL;
		ant->architect = bob;
		bob->laps_nb = 2147483647;
		bob->ants_nb = 0;
		bob->solution = NULL;
	}
	return (ant);
}

static void		delete_tubes(t_list *list)
{
	t_list		*tmp;

	if ((tmp = list) != NULL)
	{
		while (tmp != NULL)
		{
			if (tmp->content != NULL)
			{
				ft_arrdel((char ***)&tmp->content);
				tmp->content = NULL;
			}
			tmp = tmp->next;
		}
	}
}

int				main(void)
{
	char		*line;
	t_list		*tube;
	t_queen		*ant;
	void		(*func)(t_list *);

	func = delete_tubes;
	tube = NULL;
	ant = wake_queen_ant();
	ft_putendl("Please enter map. Do not use '-' except for tubes.");
	while ((get_next_line(0, &line)) >= 0)
	{
		if (!ft_strcmp(line, "") || parse_lem(line, &ant, &tube) == -1)
			break ;
		else
			free(line);
	}
	if (ft_check_map_data(&ant, &tube))
		explore_new_domain(&ant, &tube);
	else
		ft_putendl("ERROR");
	ft_lstiter(tube, func);
	ft_lstclear(&tube);
	destroy_queen(&ant);
	return (0);
}
