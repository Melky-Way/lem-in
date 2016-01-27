/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoudan <msoudan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/19 17:17:02 by msoudan           #+#    #+#             */
/*   Updated: 2014/03/22 15:46:19 by msoudan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Checks if the line is a commentary and if it announces the start or
** end flag.
*/

static int		is_com(char *line, int *start, int *end)
{
	if (line[0] == '#')
	{
		if (!(ft_strcmp(line, "##start")))
			(*start) = 2;
		else if (!(ft_strcmp(line, "##end")))
			(*end) = 1;
		return (1);
	}
	return (0);
}

static int		get_army(char *line, t_queen **ant)
{
	if (ft_isdigit_str(line))
	{
		(*ant)->ants_nb = ft_atoi(line);
		((t_architect*)(*ant)->architect)->ants_nb = (*ant)->ants_nb;
		return (0);
	}
	return (-1);
}

/*
** If the line supposed to be the end or start room has for first character #,
** L or -, it's an error. I choose to ban '-' from the room line because of
** the problems it should cause in the tube lines, which use the '-' character.
*/

static int		get_start_end(char *line, t_queen **ant, int *flag)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (line[0] == '#' || line[0] == 'L' || ft_strchr(line, '-') != 0)
		return (-1);
	while (line[i] != 0 && line[i] != ' ')
		i++;
	if (*flag == 2)
		(*ant)->end = ft_strdup(line);
	else
		(*ant)->start = ft_strdup(line);
	(*flag) = 0;
	return (0);
}

static int		add_start_end(t_queen **ant)
{
	t_list	*tmp;

	if ((*ant)->start == NULL || (*ant)->end == NULL)
		return (0);
	if (!ft_strcmp((*ant)->start, (*ant)->end))
		return (0);
	if (get_a_room((*ant)->start, &(*ant)->rooms, 0) == -1 ||
		get_a_room((*ant)->end, &(*ant)->rooms, 1) == -1)
		return (0);
	tmp = (*ant)->rooms;
	free((*ant)->start);
	(*ant)->start = ft_strdup(((t_room*)tmp->content)->name);
	while (tmp->next != NULL)
		tmp = tmp->next;
	free((*ant)->end);
	(*ant)->end = ft_strdup(((t_room*)tmp->content)->name);
	return (1);
}

int				parse_lem(char *line, t_queen **ant, t_list **tubes)
{
	static int	start_flag = 0;
	static int	end_flag = 0;
	static int	tube_flag = 0;

	if (is_com(line, &start_flag, &end_flag) == 1)
		return (0);
	else if ((*ant)->ants_nb == 0)
		return (get_army(line, ant));
	else if (start_flag != 0)
		return (get_start_end(line, ant, &start_flag));
	else if (end_flag != 0)
		return (get_start_end(line, ant, &end_flag));
	else if (line[0] != '#' && ft_strchr(line, '-') != NULL)
	{
		if (tube_flag == 0 && !add_start_end(ant))
			return (-1);
		return (get_a_tube(line, tubes, &(*ant)->rooms, &tube_flag));
	}
	else if (!tube_flag)
		return (get_a_room(line, &(*ant)->rooms, 1));
	return (-1);
}
