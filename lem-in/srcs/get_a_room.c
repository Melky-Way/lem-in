/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_a_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoudan <msoudan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/21 12:33:20 by msoudan           #+#    #+#             */
/*   Updated: 2014/03/22 15:48:06 by msoudan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** That function checks if the room coordinates are strictly numeric. If so,
** it returns the name of the room (even if it contains spaces).
*/

static char		*check_room_data(char **data)
{
	int			i;

	i = 0;
	if ((i = ft_arrlen(data)) >= 3)
	{
		if (!ft_isdigit_str(data[i - 1]) || !ft_isdigit_str(data[i - 2]))
			return (NULL);
		if (i == 3)
			return (ft_strdup(data[0]));
		return (ft_arrjoin(data, ' ', i - 2));
	}
	return (NULL);
}

static int		check_names(char *name, t_list *rooms)
{
	t_list		*tmp;

	tmp = rooms;
	while (tmp != NULL)
	{
		if (ft_strcmp(((t_room *)tmp->content)->name, name) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

/*
** That function checks if the room is not a duplicata. It creates and returns
** a t_room struct if everything is ok. OK!
*/

static t_room	*check_line(char **line, t_list **rooms)
{
	t_room		*ret;
	char		**ar;
	char		*name;

	ret = NULL;
	if ((ar = ft_strsplit(*line, ' ')) == NULL)
		return (NULL);
	if ((name = check_room_data(ar)) == NULL)
		return (NULL);
	if (check_names(name, *rooms))
	{
		free(name);
		ft_arrdel(&ar);
		return (NULL);
	}
	else
		ret = write_room(name, ar[ft_arrlen(ar) - 2], ar[ft_arrlen(ar) - 1]);
	ft_arrdel(&ar);
	return (ret);
}

/*
** That function checks if the line is not a trap and save it
** inside a linked list, removing blank spaces form the start.
*/

int				get_a_room(char *line, t_list **list, int mode)
{
	int			i;
	int			j;
	t_room		*tmp;

	i = 0;
	j = 0;
	if (line[0] == '#' || line[0] == 'L' || ft_strchr(line, '-') != 0)
		return (-1);
	while (line[i] != 0 && line[i] != ' ')
		i++;
	if ((tmp = check_line(&line, list)) == NULL)
		return (-1);
	if (!mode)
		ft_lstpushback(list, tmp, sizeof(tmp));
	else
		ft_lstpushfront(list, tmp, sizeof(tmp));
	return (0);
}
