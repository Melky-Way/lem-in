/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   explore_new_domain.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoudan <msoudan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 15:13:59 by msoudan           #+#    #+#             */
/*   Updated: 2016/06/14 14:17:13 by msoudan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		destroy_map(t_room **map)
{
	int			i;

	i = -1;
	if ((*map) != NULL && (*map)->tubes != NULL)
	{
		while ((*map)->tubes[++i] != NULL)
			destroy_map(&(*map)->tubes[i]);
		free((*map)->tubes);
		(*map)->tubes = NULL;
	}
	erase_room(map);
}

static void		sort_by_size(t_list *paths)
{
	t_list		*elem1;
	t_list		*elem2;

	if ((elem1 = paths) == NULL)
		return ;
	elem2 = paths->next;
	while (elem1 != NULL && (elem2 = elem1->next) != NULL)
	{
		if (((t_dlist *)elem1->content)->lenght >
			((t_dlist *)elem2->content)->lenght)
		{
			ft_lst_swap(elem1, elem2);
			elem1 = paths;
		}
		else
			elem1 = elem1->next;
	}
}

static void		print_map_core(t_list *tmp)
{
	ft_putstr(((t_room *)tmp->content)->name);
	ft_putchar(' ');
	ft_putnbr(((t_room *)tmp->content)->x);
	ft_putchar(' ');
	ft_putnbr(((t_room *)tmp->content)->y);
	ft_putchar('\n');
}

static void		print_map(t_queen **ant, t_list **tubes)
{
	t_list		*tmp;

	ft_putnbr((*ant)->ants_nb);
	ft_putchar('\n');
	tmp = (*ant)->rooms;
	while (tmp != NULL)
	{
		if (!ft_strcmp(((t_room *)tmp->content)->name, (*ant)->start))
			ft_putendl("#start");
		else if (tmp->next == NULL)
			ft_putendl("#exit");
		print_map_core(tmp);
		tmp = tmp->next;
	}
	tmp = *tubes;
	while (tmp != NULL)
	{
		ft_putstr(((char **)tmp->content)[0]);
		ft_putchar('-');
		ft_putendl(((char **)tmp->content)[1]);
		tmp = tmp->next;
	}
}

/*
** For an optimal use of bob_at_work, *tmp is a copy of the first link of *ways
** and way is put to his next iteration.
*/

void			explore_new_domain(t_queen **ant, t_list **tubes)
{
	t_room		*full_map;
	t_list		*scroll;
	t_list		*tmp;
	void		(*func1)(t_list *);

	func1 = delete_content_list;
	print_map(ant, tubes);
	ft_putchar('\n');
	scroll = NULL;
	full_map = draw_room((*ant)->start, NULL, tubes, ant);
	send_scouts(&full_map, ant, &scroll);
	destroy_map(&full_map);
	if (scroll != NULL)
	{
		tmp = ft_create_new(scroll->content, scroll->content_size);
		bob_at_work((*ant)->architect, scroll->next, tmp);
		sort_by_size((*ant)->architect->solution);
		if ((*ant)->architect->solution != NULL)
			send_army((*ant)->architect, NULL);
		delete_current_test(&(*ant)->architect->solution);
		delete_ways(scroll);
		return ;
	}
	ft_putendl("ERROR");
}
