/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_a_tube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoudan <msoudan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/09 13:44:17 by msoudan           #+#    #+#             */
/*   Updated: 2015/11/09 13:44:19 by msoudan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** This function checks if the tunnel links two existing rooms. OK!
*/

static int	check_tubes_names(char **tube, t_list **rooms)
{
	t_list	*tmp;
	int		break_flag;

	tmp = *rooms;
	break_flag = 0;
	while (tmp != NULL && break_flag < 2)
	{
		if (ft_strcmp(tube[0], ((t_room *)tmp->content)->name) == 0 ||
			ft_strcmp(tube[1], ((t_room *)tmp->content)->name) == 0)
			break_flag++;
		tmp = tmp->next;
	}
	return (break_flag < 2 ? 0 : 1);
}

/*
** This function check if the tube links the same room, or if this tube is
** already saved.
*/

static int	check_circle_tubes(char **tube, t_list **tubes)
{
	t_list	*tmp;

	if (ft_strcmp(tube[0], tube[1]) == 0)
		return (0);
	tmp = (*tubes);
	while (tmp != NULL)
	{
		if ((!ft_strcmp(tube[0], ((char **)tmp->content)[0]) &&
				!ft_strcmp(tube[1], ((char **)tmp->content)[1])) ||
			(!ft_strcmp(tube[0], ((char **)tmp->content)[1]) &&
				!ft_strcmp(tube[1], ((char **)tmp->content)[0])))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

/*
** This function check sif the tube is correct, checking if the tube connects
** two existing rooms or is not a repetition. If so, it's discarded and life
** goes on. OK!
*/

int			get_a_tube(char *line, t_list **tubes, t_list **rooms, int *flag)
{
	char	**tube;

	if ((tube = ft_strsplit(line, '-')) != NULL && ft_arrlen(tube) == 2)
	{
		if (!check_tubes_names(tube, rooms) ||
			!check_circle_tubes(tube, tubes))
		{
			ft_arrdel(&tube);
			return (0);
		}
		ft_lstpushback(tubes, (void *)tube, sizeof(tube));
		(*flag)++;
		return (0);
	}
	return (-1);
}
