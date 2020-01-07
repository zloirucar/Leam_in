/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bhandari.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 18:21:40 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/07 21:57:35 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	save_paths(t_map *map)
{
	t_cell *cur;
	t_cell *prev;
	t_path *thispath;

	thispath = NULL;
	cur = map->arr_cell[map->end];
	while (cur != map->arr_cell[map->start])
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
		if (ft_strstr(map->arr_cell[cur_cell->index]->name, find_name))
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
	cur = map->arr_cell[map->end];
	while (cur != map->arr_cell[map->start])
	{
		prev = cur->prev;
		thispath = path_addlast(thispath, cur);
		prev->next_neib = del_neib(map, prev->next_neib, cur->name);
		if (!(revert_weights(map, cur->next_neib, prev->name)))
		{
			map->delete_path = path_addlast(map->delete_path, cur);
			map->delete_path = path_addlast(map->delete_path, prev);
		}
		map->edges = remove_used_edge(map, cur->name, prev->name);
		cur = cur->prev;
	}
	thispath = path_addlast(thispath, cur);
	thispath = revert_path(thispath);
	map->rev_paths = paths_addlast(map->rev_paths, thispath);
}

void	bhandari_algo(t_map *map)
{
	while (shortest_path(map))
	{
		bellman_ford_weights(map);
		update_map(map);
	}
	return_neib(map);
	delete_path(map);
	update_map(map);
	while (shortest_path(map))
	{
		save_paths(map);
		update_map(map);
	}
}
