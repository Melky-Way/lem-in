/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scouts_report.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoudan <msoudan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 19:46:53 by msoudan           #+#    #+#             */
/*   Updated: 2014/03/23 20:38:01 by msoudan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#define PREV_IS_BIGGER ((*map)->prev->rooms_nbr > ((*map)->rooms_nbr + 1))

void		destroy_all_but_one(t_room **map)
{
	int		i;
	t_room	*del;

	i = -1;
	if ((*map) != NULL && (*map)->tubes != NULL)
	{
		while ((*map)->tubes[++i] != NULL)
		{
			destroy_all_but_one(&(*map)->tubes[i]);
			if ((*map)->rooms_nbr != (*map)->tubes[i]->rooms_nbr + 1)
			{
				del = (*map)->tubes[i];
				redraw_sign_tubes(map, i);
				destroy_map(&del);
				i--;
			}
		}
	}
}

void		scouts_report(t_room **map, t_queen **ant)
{
	int		i;

	i = -1;
	if ((*map) != NULL && (*map)->tubes != NULL)
	{
		while ((*map)->tubes[++i] != NULL)
			scouts_report(&(*map)->tubes[i], ant);
		if ((*map)->prev != NULL && PREV_IS_BIGGER)
			(*map)->prev->rooms_nbr = (*map)->rooms_nbr + 1;
	}
	else if ((*map)->tubes == NULL && !ft_strcmp((*map)->name, (*ant)->end))
	{
		(*map)->rooms_nbr = 0;
		if ((*map)->prev != NULL && PREV_IS_BIGGER)
			(*map)->prev->rooms_nbr = (*map)->rooms_nbr + 1;
	}
}
