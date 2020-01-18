/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 17:59:02 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/17 17:32:51 by skrabby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		visit_nodes_neighbours(t_map *map, t_cell *this_node)
{
	t_neib	*tmp;
	int		weight;

	tmp = this_node->next_neib;
	while (tmp)
	{
		weight = get_weight(map, this_node->next_neib,
		map->arr_cell[tmp->index]->cell->name);
		if (!map->arr_cell[tmp->index]->cell->is_visited)
		{
			if ((this_node->distance + weight
			< map->arr_cell[tmp->index]->cell->distance)
			|| map->arr_cell[tmp->index]->cell->distance == 0)
			{
				map->arr_cell[tmp->index]->cell->distance =
				this_node->distance + weight;
				map->arr_cell[tmp->index]->cell->prev = this_node;
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
	t_neib	*cur_cell;

	if (list == NULL)
		return (0);
	cur_cell = list;
	while (cur_cell)
	{
		if (!ft_strcmp(map->arr_cell[cur_cell->index]->cell->name, find_name))
			return (cur_cell->weight);
		cur_cell = cur_cell->next;
	}
	return (0);
}

int		visit_node(t_map *map, t_cell *prev_node, t_cell *new_node)
{
	int weight;

	weight = get_weight(map, prev_node->next_neib, new_node->name);
	if ((prev_node->distance + weight
	< new_node->distance) || new_node->distance == 0)
	{
		new_node->prev = prev_node;
		new_node->distance = prev_node->distance + weight;
	}
	new_node->is_visited = 1;
	if (new_node == map->arr_cell[map->end]->cell)
		return (1);
	else if (visit_nodes_neighbours(map, new_node))
		return (1);
	else
		return (0);
}
