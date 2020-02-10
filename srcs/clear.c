/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 15:44:39 by oelaina           #+#    #+#             */
/*   Updated: 2020/02/10 18:46:14 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	clear_cell(t_cell **cell)
{
	t_cell *tmp;
	t_cell *buf;

	tmp = *cell;
	while (tmp != NULL)
	{
		buf = tmp;
		tmp = tmp->next;
		free(buf);
		buf = NULL;
	}
}

void	clear_path(t_path **path)
{
	t_path *tmp;
	t_path *buf;

	tmp = *path;
	while (tmp != NULL)
	{
		buf = tmp;
		tmp = tmp->next;
		free(buf);
	}
}

void	clear_finpath(t_finpaths **paths)
{
	t_path *tmp;
	t_path *buf;

	buf = NULL;
	tmp = (*paths)->path;
	while (buf != NULL && tmp->prev != NULL)
		tmp = tmp->prev;
	while (tmp != NULL)
	{
		buf = tmp;
		tmp = tmp->next;
		free(buf);
	}
	free(*paths);
}

void	clear_list_finpath(t_finpaths **paths)
{
	t_finpaths *tmp;
	t_finpaths *buf;

	tmp = *paths;
	while (tmp != NULL)
	{
		buf = tmp;
		tmp = tmp->next;
		clear_finpath(&buf);
		buf = NULL;
	}
}
