/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_current_test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoudan <msoudan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/18 11:41:49 by msoudan           #+#    #+#             */
/*   Updated: 2016/06/13 20:47:46 by msoudan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

/*
** Put content to null to avoid deleting it when destroying soft copies.
*/

static void		ft_lst_resetcontent(t_list *elem)
{
	elem->content = NULL;
	return ;
}

void			delete_current_test(t_list **test)
{
	void		(*func1)(t_list *);

	func1 = ft_lst_resetcontent;
	if (*test != NULL)
	{
		ft_lstiter(*test, ft_lst_resetcontent);
		ft_lstclear(test);
	}
	return ;
}
