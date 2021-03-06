/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 18:07:26 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/18 22:12:27 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_finpaths	*init_finpaths(void)
{
	t_finpaths *tmp;

	if (!(tmp = (t_finpaths *)malloc(sizeof(t_finpaths))))
		exit(1);
	tmp->next = NULL;
	return (tmp);
}

t_finpaths	*paths_addlast(t_finpaths *list, t_path *new_path)
{
	t_finpaths *tmp;

	tmp = NULL;
	if (list == NULL)
	{
		list = init_finpaths();
		list->path = new_path;
	}
	else
	{
		tmp = list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = init_finpaths();
		tmp = tmp->next;
		tmp->path = new_path;
	}
	return (list);
}

void		check_name_list(t_cell **tmp, char *name)
{
	while ((*tmp)->next)
	{
		if (ft_strcmp((*tmp)->name, name) == 0)
			error_msg();
		(*tmp) = (*tmp)->next;
	}
	if (ft_strcmp((*tmp)->name, name) == 0)
		error_msg();
}
