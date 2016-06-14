/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoudan <msoudan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/23 11:50:16 by msoudan           #+#    #+#             */
/*   Updated: 2016/06/13 20:47:38 by msoudan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# include "../libft/libft.h"

typedef struct		s_room
{
	char			*name;
	char			*ant;
	int				y;
	int				x;
	struct s_room	*prev;
	struct s_room	**tubes;
}					t_room;

/*
** Architects know ways. The architect knows the best path and is a source of
** data for a section of the anthill. If there's a way, he knows it.
*/

typedef struct		s_architect
{
	size_t			laps_nb;
	int				ants_nb;
	t_list			*solution;
}					t_architect;

/*
** The Queen rules everything. She commands the ant legion. She is advised
** by the architect.
*/

typedef struct		s_queen
{
	char			*start;
	char			*end;
	int				ants_nb;
	t_list			*rooms;
	t_architect		*architect;
}					t_queen;

typedef struct		s_ant
{
	char			*name;
	void			*room;
}					t_ant;

/*
** main.c
*/

int					main(void);
/*
** parse_lem.c
*/

int					parse_lem(char *line, t_queen **ant, t_list **tubes);
/*
** draw_room.c
*/

t_room				*draw_room(char *name, t_room *prev, t_list **tubes, \
					t_queen **ant);
/*
** get_a_room.c
*/

int					get_a_room(char *line, t_list **list, int mode);
/*
** get_a_tube.c
*/

int					get_a_tube(char *line, t_list **tubes, t_list **rooms, \
					int *flag);
/*
** explore_new_domain.c
*/

void				explore_new_domain(t_queen **ant, t_list **tubes);
/*
** wrong_turn.c
*/

int					wrong_turn(char *name, t_room *map);
/*
** send_scouts.c
*/

int					send_scouts(t_room **map, t_queen **ant, t_list **scroll);
/*
** send_army.c
*/

int					send_army(t_architect *bob, t_list *army);
/*
** write_room.c
*/

t_room				*write_room(char *name, char *x, char *y);
/*
** get_x_y.c
*/

void				get_x_y(t_room *new_room, char *name, t_queen **ant);
/*
** bob_at_work.c
*/

void				bob_at_work(t_architect *bob, t_list *ways, \
					t_list *current);
/*
** test_compatibility.c
*/

int					test_compatibility(t_list *test);
/*
** delete_ways.c
*/

void				delete_ways(t_list *list);
void				erase_room(t_room **map);
void				delete_content_dlist(t_dbl *element);
void				delete_content_list(t_list *element);
/*
** delete_current_test.c
*/

void				delete_current_test(t_list **test);

#endif
