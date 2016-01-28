/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_compatibility.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoudan <msoudan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/10 18:46:15 by msoudan           #+#    #+#             */
/*   Updated: 2015/11/10 18:46:17 by msoudan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Function comparing rooms name. Stops when the names are identical.
*/

static int		duplicata_found(t_list *a, t_list *b)
{
	t_dbl		*tmp1;
	t_dbl		*tmp2;
	char		*name1;
	char		*name2;

	if (a != NULL & b != NULL)
	{
		tmp1 = ((t_dlist *)a->content)->head->next;
		tmp2 = ((t_dlist *)b->content)->head->next;
		while (tmp1 != NULL && tmp1->next != NULL)
		{
			while (tmp2 != NULL && tmp2->next != NULL)
			{
				name1 = ((t_room *)tmp1->content)->name;
				name2 = ((t_room *)tmp2->content)->name;
				if (!ft_strcmp(name1, name2))
					return (1);
				tmp2 = tmp2->next;
			}
			tmp1 = tmp1->next;
			tmp2 = ((t_dlist *)b->content)->head->next;
		}
	}
	return (0);
}

/*
** Test if one way crosses path with another, rendering that path combination
** useless.
*/

int				test_compatibility(t_list *test)
{
	t_list		*tmp1;
	t_list		*tmp2;

	if (test != NULL)
	{
		tmp1 = test;
		while (tmp1 != NULL)
		{
			tmp2 = tmp1->next;
			while (tmp2 != NULL)
			{
				if (duplicata_found(tmp1, tmp2))
					return (1);
				tmp2 = tmp2->next;
			}
			tmp1 = tmp1->next;
		}
	}
	return (0);
}
