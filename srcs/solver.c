/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 21:19:08 by skrabby           #+#    #+#             */
/*   Updated: 2020/01/18 19:06:47 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_cell	*checklist_addlast(t_cell *checklist, t_cell *new)
{
	t_cell *tmp;

	tmp = checklist;
	if (tmp == NULL)
	{
		tmp = new;
		tmp->sp_next = NULL;
	}
	else
	{
		while (tmp->sp_next)
			tmp = tmp->sp_next;
		tmp->sp_next = new;
		tmp->sp_next->sp_next = NULL;
	}
	return (checklist);
}

void	save_paths(t_map *map)
{
	t_cell *cur;
	t_cell *prev;
	t_path *thispath;

	thispath = NULL;
	cur = map->arr_cell[map->end]->cell;
	while (cur != map->arr_cell[map->start]->cell)
	{
		prev = cur->prev;
		thispath = path_addlast(thispath, cur);
		prev->next_neib = del_neib(map, prev->next_neib, cur->name);
		cur->next_neib = del_neib(map, cur->next_neib, prev->name);
		cur = cur->prev;
	}
	thispath = path_addlast(thispath, cur);
	thispath = revert_path(thispath);
	map->paths = paths_addlast(map->paths, thispath);
}

int		revert_weights(t_map *map, t_neib *list, char *find_name)
{
	t_neib *cur_cell;

	cur_cell = list;
	while (cur_cell)
	{
		if (!ft_strcmp(map->arr_cell[cur_cell->index]->cell->name, find_name))
		{
			cur_cell->weight *= -1;
			return (1);
		}
		cur_cell = cur_cell->next;
	}
	return (0);
}

void	bellman_ford_weights(t_map *map)
{
	t_cell *cur;
	t_cell *prev;
	t_path *thispath;

	thispath = NULL;
	cur = map->arr_cell[map->end]->cell;
	while (cur != map->arr_cell[map->start]->cell)
	{
		prev = cur->prev;
		thispath = path_addlast(thispath, cur);
		prev->next_neib = del_neib(map, prev->next_neib, cur->name);
		if (!(revert_weights(map, cur->next_neib, prev->name)))
		{
			map->delete_path = path_addlast(map->delete_path, cur);
			map->delete_path = path_addlast(map->delete_path, prev);
		}
		cur = cur->prev;
	}
	thispath = path_addlast(thispath, cur);
	thispath = revert_path(thispath);
	map->rev_paths = paths_addlast(map->rev_paths, thispath);
}

int		checkcollision(t_map *map)
{
	while (shortest_path(map))
	{
		bellman_ford_weights(map);
		update_map(map, NULL);
	}
	return_neib(map);
	update_map(map, NULL);
	return (map->delete_path ? 1 : 0);
		
}

void	bhandari_algo(t_map *map)
{
	if (checkcollision(map))
	{
		delete_path(map);
		bhandari_algo(map);
	}
	else
	{
		while (shortest_path(map))
		{
			save_paths(map);
			update_map(map, map->paths);
		}
	}
}
