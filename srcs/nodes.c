/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 17:59:02 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/06 18:04:36 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int visit_nodes_neighbours(t_map *map, t_cell *this_node)
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
				//			if (weight == -1)
				//			{
				//	printf("DELETE ROUTE: %s, %s\n", this_node->name, map->arr_cell[tmp->index]->name);
				//	del_neib(map, this_node->next_neib, map->arr_cell[tmp->index]->name);
				//				map->delete_path = path_addlast(map->delete_path, this_node);
				//				map->delete_path = path_addlast(map->delete_path, map->arr_cell[tmp->index]);
				//			}
			}
		}
		if (map->arr_cell[tmp->index] == map->arr_cell[map->end])
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int     get_weight(t_map *map, t_neib *list, char *find_name)
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

int     visit_node(t_map *map, t_cell *prev_node, t_cell *new_node)
{
	int weight;

	weight = get_weight(map, prev_node->next_neib, new_node->name);
	if ((prev_node->distance + weight < new_node->distance) || new_node->distance == 0)
	{
		new_node->prev = prev_node;
		new_node->distance = prev_node->distance + weight;
	}
	new_node->is_visited = 1;
	if (new_node == map->arr_cell[map->end])
		return (1);
	else if (visit_nodes_neighbours(map, new_node))
		return (1);
	else
		return (0);
}