/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 18:13:43 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/06 18:24:18 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int shortest_path(t_map *map)
{
	t_cell *cur;
	t_cell *prev;
	t_cell *checklist;
	t_neib *tmp;

	checklist = map->arr_cell[map->start];
	cur = map->arr_cell[map->start];
	prev = cur;
	cur->is_visited = 1;
	cur->distance = 0;
	while (cur != map->arr_cell[map->end] && checklist)
	{
		prev = checklist;
		printf("(PREV) NAME: %s\n", prev->name);
		tmp = prev->next_neib;
		while (tmp)
		{
			cur = map->arr_cell[tmp->index];
			printf("(CURR) NAME: %s, DISTANCE: %d, ISVISITED: %d\n", cur->name, cur->distance, cur->is_visited);
			if (!cur->is_visited)
			{
				checklist = checklist_addlast(checklist, cur);
				if (visit_node(map, prev, cur))
				{
					printshort(map);
					return (1);
				}
			}
			tmp = tmp->next;
		}
		checklist = checklist->next;
	}
	return (0);
}

void update_map(t_map *map)
{
	int i;

	i = 0;
	while (i < map->size_arr)
	{
		map->arr_cell[i]->distance = 0;
		map->arr_cell[i]->is_visited = 0;
		map->arr_cell[i]->prev = NULL;
		map->arr_cell[i]->next = NULL;
		i++;
	}
}

void print_shortest(t_path *list)
{
	t_path *tmp;

	if (!list)
		return;
	tmp = list;
	printf("ADSPOASDJASOPDJ\n");
	while (tmp)
	{
		printf("SHORT ROUTE: %s\n", tmp->cell->name);
		tmp = tmp->next;
	}
}

void return_neib(t_map *map)
{
	t_finpaths *tmp;

	tmp = map->rev_paths;
	while (tmp)
	{
		while (tmp->path->next)
		{
			printf("RETURN CELL NAME: %s\n", tmp->path->cell->name);
			printf("RETURN CELL NEIB: %s\n", tmp->path->next->cell->name);
			tmp->path->cell->next_neib = neib_addlast(tmp->path->cell->next_neib, tmp->path->next->cell->index);
			revert_weights(map, tmp->path->next->cell->next_neib, tmp->path->cell->name);
			tmp->path = tmp->path->next;
		}
		tmp = tmp->next;
	}
}
