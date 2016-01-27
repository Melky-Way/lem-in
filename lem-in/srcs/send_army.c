/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_army.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoudan <msoudan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/23 20:38:12 by msoudan           #+#    #+#             */
/*   Updated: 2014/03/26 14:23:34 by msoudan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#define ENOUGH_TIME (bob->laps_nb >= ((t_dlist *)tmp->content)->lenght - 1)

static char		*name(int ant_name)
{
	char		*number;
	char		*name_tag;

	number = ft_itoa(ant_name);
	name_tag = ft_strjoin("L", number);
	free(number);
	number = NULL;
	return (name_tag);
}

static void		print_army(t_list *army, int *space_flag, int *count)
{
	t_list		*tmp;
	t_dbl		*room;
	t_ant		*soldier;

	if ((tmp = army) != NULL)
	{
		while (tmp != NULL)
		{
			soldier = (t_ant *)tmp->content;
			if ((room = (t_dbl *)soldier->room) != NULL)
			{
				if (*space_flag)
					ft_putchar(' ');
				(*space_flag)++;
				ft_putstr(soldier->name);
				ft_putchar('-');
				ft_putstr(((t_room *)room->content)->name);
				soldier->room = (void *)room->next;
				if (soldier->room == NULL)
					(*count)++;
			}
			tmp = tmp->next;
		}
	}
}

static t_ant	*ant(char *name, t_list *way)
{
	t_ant		*soldier;

	if ((soldier = (t_ant *)malloc(sizeof(t_ant))) != NULL)
	{
		soldier->name = name;
		soldier->room = (void *)((t_dlist *)way->content)->head->next;
		return (soldier);
	}
	return (NULL);
}

static void		delete_army(t_list **army)
{
	t_list		*tmp;
	t_ant		*ant;

	if ((tmp = *army) != NULL)
	{
		while (tmp != NULL)
		{
			if ((ant = (t_ant *)tmp->content) != NULL)
			{
				if (ant->name != NULL)
					free(ant->name);
			}
			tmp = tmp->next;
		}
		ft_lstclear(army);
	}
}

int				send_army(t_architect *bob, t_list *army)
{
	int			tag;
	int			count;
	int			space_flag;
	t_list		*tmp;

	tag = 0;
	count = 0;
	ft_putstr("Total: ");
	ft_putstr(ft_itoa(bob->laps_nb));
	ft_putendl(" laps.\n");
	while (count != bob->ants_nb && (tmp = bob->solution) != NULL)
	{
		space_flag = 0;
		while (tmp != NULL && tmp->content != NULL)
		{
			if (tag < bob->ants_nb && ENOUGH_TIME)
				ft_lstpushback(&army, ant(name(++tag), tmp), sizeof(t_ant));
			tmp = tmp->next;
		}
		print_army(army, &space_flag, &count);
		bob->laps_nb--;
		ft_putchar('\n');
	}
	delete_army(&army);
	return (0);
}
