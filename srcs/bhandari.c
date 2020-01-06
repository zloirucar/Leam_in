/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bhandari.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 18:21:40 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/06 18:41:23 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void    save_paths(t_map *map)
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

int     revert_weights(t_map *map, t_neib *list, char *find_name)
{
	t_neib *cur_cell;

	cur_cell = list;
	while (cur_cell)
	{
		if (ft_strstr(map->arr_cell[cur_cell->index]->name, find_name))
		{
			cur_cell->weight *= -1;
			printf("CHECK WEIGHT:  NAME:%s WEIGHT: %d\n", map->arr_cell[cur_cell->index]->name, cur_cell->weight);
			return (1);
		}
		cur_cell = cur_cell->next;
	}
	return (0);
}

void bellman_ford_weights(t_map *map)
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

void bhandari_algo(t_map *map)
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
	/*
	shortest_path(map); // find shortest path
	bellman_ford_weights(map); // revert weights of sp
	update_map(map); // update new map
	shortest_path(map); // find sp again
	return_neib(map); // revert weights and route back to normal
	delete_path(map); // delete intersected paths
	update_map(map); // update map once again
	shortest_path(map); // our final paths;
	save_paths(map); // save it + delete the route
	update_map(map);*/
	//print_shortest(map->shortest_path);
	//print_shortest(map->delete_path);
}