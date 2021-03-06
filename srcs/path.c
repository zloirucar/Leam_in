/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 18:01:56 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/06 19:22:20 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_path	*init_path(void)
{
	t_path *tmp;

	if (!(tmp = (t_path *)malloc(sizeof(t_path))))
		exit(1);
	tmp->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}

t_path	*path_addlast(t_path *alst, t_cell *cell)
{
	t_path *tmp;

	tmp = NULL;
	if (alst == NULL)
	{
		alst = init_path();
		alst->cell = cell;
	}
	else
	{
		tmp = alst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = init_path();
		tmp->next->cell = cell;
	}
	return (alst);
}

t_path	*revert_path(t_path *path)
{
	t_path *prev;
	t_path *curr;
	t_path *next;

	curr = path;
	prev = NULL;
	next = path;
	while (curr != NULL)
	{
		next = next->next;
		curr->next = prev;
		prev = curr;
		curr = next;
		prev->prev = curr;
	}
	return (prev);
}

void	delete_path(t_map *map)
{
	t_path *tmp;
	t_cell *one;
	t_cell *two;

	tmp = map->delete_path;
	while (tmp)
	{

		one = map->arr_cell[search_cell(map, tmp->cell->name)]->cell;
		two = map->arr_cell[search_cell(map, tmp->next->cell->name)]->cell;
		one->next_neib =
		del_neib(map, one->next_neib, two->name);
		two->next_neib =
		del_neib(map, two->next_neib, one->name);
		tmp = tmp->next->next;
	}
}
