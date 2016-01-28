/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bob_at_work.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoudan <msoudan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/10 13:18:16 by msoudan           #+#    #+#             */
/*   Updated: 2015/11/10 13:18:19 by msoudan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Calculate the number of laps needed to tranfer all the ants with this
** combination of roads.
*/

static size_t	send_probe(t_architect *bob, t_list *test)
{
	size_t		i;
	t_list		*tmp;
	int			ants_nb;

	if (bob != NULL)
	{
		ants_nb = bob->ants_nb;
		i = 0;
		while (ants_nb > 0)
		{
			tmp = test;
			i++;
			while (tmp != NULL)
			{
				if (i >= ((t_dlist *)tmp->content)->lenght - 1)
					ants_nb--;
				tmp = tmp->next;
			}
		}
		if (i < bob->laps_nb)
			return (i);
	}
	return (0);
}

static void		replace_best(t_architect *bob, t_list *current)
{
	t_list		*tmp;
	size_t		best;

	best = send_probe(bob, current);
	if (bob != NULL && current != NULL && best)
	{
		delete_current_test(&(bob)->solution);
		bob->laps_nb = best;
		if ((tmp = current) != NULL)
		{
			while (tmp != NULL)
			{
				ft_lstpushback(&(bob)->solution, tmp->content,
											tmp->content_size);
				tmp = tmp->next;
			}
		}
	}
}

/*
** Recursive function to combine roads to determine the best possible solution.
*/

void			bob_at_work(t_architect *bob, t_list *ways, t_list *current)
{
	t_list		*tmp;
	t_list		*cpy;
	static int	limit = 0;

	tmp = ways;
	if (limit++ > 50)
		return ;
	if (current != NULL && !test_compatibility(current))
	{
		replace_best(bob, current);
		if (tmp != NULL && (cpy = ft_lst_softcopy(current)) != NULL)
		{
			ft_lstpushback(&cpy, (void *)(tmp)->content, tmp->content_size);
			bob_at_work(bob, tmp->next, cpy);
		}
	}
	if (tmp != NULL)
	{
		ft_lst_swaptail(tmp, &current);
		bob_at_work(bob, tmp->next, ft_lst_softcopy(current));
		tmp = tmp->next;
	}
	delete_current_test(&current);
	return ;
}
