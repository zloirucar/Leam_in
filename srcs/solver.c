/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 21:19:08 by skrabby           #+#    #+#             */
/*   Updated: 2019/12/29 15:51:48 by skrabby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//Bhandari Disjoint Path Finding

void	delete_shortest_path()
{
}


void	visit_nodes_neighbours(t_cell *this_node, int distance)
{
	int	i;
	i = 0;

	while (this_node->neib[i])
	{ 
		if (!this_node->neib[i]->is_visited)
		{
			if ((distance < this_node->neib[i]->distance) || this_node->neib[i]->distance == 0)
			{
				this_node->neib[i]->distance = distance;
				this_node->neib[i]->prev = this_node;
			}
		}
		i++;
	}
}

void	visit_node(t_cell *prev_node, t_cell *new_node, int distance)
{
	if ((distance < new_node->distance) || new_node->distance == 0)
	{
		new_node->prev = prev_node;
		new_node->distance = distance;
	}
	visit_nodes_neighbours(new_node, distance + 1);
	new_node->is_visited = 1;
}

//Dijkstra's Algorithm

int		shortest_path(t_map *map)
{
	t_cell *cur;
	t_cell *prev;
	int		distance;
	int		i;
	
	distance = 0;
	i = 0;
	cur = map->start;
	while (cur != map->end)
	{
		i = 0;
		distance++;
		prev = cur;
		while (prev->neib[i])
		{
			cur = prev->neib[i];
			if (!cur->is_visited)
				visit_node(prev, cur, distance);
			i++;
		}
	}

}

t_cell	**new_path(t_cell **paths)
{
	unsigned int	i;

	i = 0;
	while (paths[i])
		i++;
	if (!(paths[i] = (t_cell *)ft_memalloc(sizeof(t_cell))));
		exit (1);
	return (paths);
}

void	solver(t_map *map)
{
	int	i;

	i = 0;
	map->paths = (t_cell **)ft_memalloc(sizeof(t_cell*) * map->count + 1); // map->count ?? number of cells
	map->paths = new_path(map->paths);
}