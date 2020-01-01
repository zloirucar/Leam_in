/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 21:19:08 by skrabby           #+#    #+#             */
/*   Updated: 2019/12/30 21:18:28 by skrabby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	visit_nodes_neighbours(t_map *map, t_cell *this_node)
{

	t_neib *tmp;
	int weight;

	tmp = this_node->next_neib;
	while (tmp)
	{
		weight = get_weight(map, this_node->next_neib, map->arr_cell[tmp->index]->name);
		printf("INDEX: %d:\n", tmp->index);
		printf("NEIB: %s\n", map->arr_cell[tmp->index]->name);
		if (!map->arr_cell[tmp->index]->is_visited)
		{
			if ((this_node->distance + weight < map->arr_cell[tmp->index]->distance) || map->arr_cell[tmp->index]->distance == 0)
			{
				map->arr_cell[tmp->index]->distance = this_node->distance + weight;
				map->arr_cell[tmp->index]->prev = this_node;
			}
		}
		if (map->arr_cell[tmp->index] == map->arr_cell[map->end])
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int		get_weight(t_map *map, t_neib *list, char *find_name)
{
	t_neib *cur_cell;

	if (list == NULL)
		return (0);
	cur_cell = list;
	while (cur_cell)
	{

		if (ft_strstr(map->arr_cell[cur_cell->index]->name, find_name))
		{
			printf("WEIGHT: %d\n", cur_cell->weight);
			return (cur_cell->weight);
		}
		cur_cell = cur_cell->next;
	}
	return (0);
}

int		visit_node(t_map *map, t_cell *prev_node, t_cell *new_node)
{
	if ((prev_node->distance + 1 < new_node->distance) || new_node->distance == 0)
	{
		new_node->prev = prev_node;
		new_node->distance = prev_node->distance + get_weight(map, prev_node->next_neib, new_node->name);
	}	
	new_node->is_visited = 1;
	if (visit_nodes_neighbours(map, new_node))
		return (1);
	else
		return (0);
}

t_cell		*checklist_addlast(t_cell *checklist, t_cell *new)
{
	t_cell *tmp;

	tmp = checklist;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	tmp->next->next = NULL;
	return (checklist);
}

void		printshort(t_map *map)
{
	t_cell *tmp;

	tmp = map->arr_cell[map->end];
	printf("ROUTE: %s  DISTANCE %d\n", tmp->name, tmp->distance);
	while (tmp != map->arr_cell[map->start])
	{
		tmp = tmp->prev;
		printf("ROUTE: %s  DISTANCE %d\n", tmp->name, tmp->distance);
	}
}

//Dijkstra's Algorithm

void		shortest_path(t_map *map)
{
	t_cell *cur;
	t_cell *prev;
	t_cell *checklist;
	t_neib *tmp;

	checklist = NULL;
	cur = map->arr_cell[map->start];
	prev = cur;
	cur->is_visited = 1;
	cur->distance = 0;
	while (cur != map->arr_cell[map->end])
	{
		if (checklist == NULL)
			checklist = map->arr_cell[map->start];
		else 
			checklist = checklist->next;
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
						return;
				}
			}
			tmp = tmp->next;
		}
	}
}

void		reload_map(t_map *map)
{
	int i;

	i = 0;
	while (i < map->size_arr)
	{
		map->arr_cell[i]->distance = 0;
		map->arr_cell[i]->is_visited = 0;
		map->arr_cell[i]->prev = NULL;
		i++;
	}
}

void	revert_weights(t_map *map, t_neib *list, char *find_name)
{
	t_neib *cur_cell;

	if (list == NULL)
		return;
	cur_cell = list;
	while (cur_cell)
	{

		if (ft_strstr(map->arr_cell[cur_cell->index]->name, find_name))
		{
			printf("SOOQABLYAT, %s\n", map->arr_cell[cur_cell->index]->name);
			cur_cell->weight = -1;
		}
		cur_cell = cur_cell->next;
	}
}

//Bhandari Disjoint Path Finding

void		bhandari_algo(t_map *map)
{
	t_cell *cur;
	t_cell *prev;

	cur = map->arr_cell[map->end];
	while (cur != map->arr_cell[map->start])
	{
		prev = cur->prev;
		del_neib(map, prev->next_neib, cur->name);
		revert_weights(map, cur->next_neib, prev->name);
		cur = cur->prev;
	}
	reload_map(map);
	shortest_path(map);
}