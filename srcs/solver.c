/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 21:19:08 by skrabby           #+#    #+#             */
/*   Updated: 2019/12/29 21:38:32 by skrabby          ###   ########.fr       */
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

	ft_printf("T: %d\n", this_node->size_neib);
	while (i < this_node->size_neib)
	{ 
		ft_printf("NEIB: %s\n", this_node->neib[i]->name);
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

int		visit_node(t_map *map, t_cell *prev_node, t_cell *new_node, int distance)
{
	ft_printf("S: %s, %d, %d, %d\n", new_node->name, new_node->y, new_node->x, new_node->size_neib);
	//ft_printf("T: %s, %d, %d, %d\n", map->arr_cell[4]->name, map->arr_cell[4]->y, map->arr_cell[4]->x, map->arr_cell[4]->size_neib);
	if ((distance < new_node->distance) || new_node->distance == 0)
	{
		new_node->prev = prev_node;
		new_node->distance = distance;
	}
	visit_nodes_neighbours(new_node, distance + 1);
	new_node->is_visited = 1;
	if (new_node == map->arr_cell[map->end])
		return (1);
	else
		return (0);
}

//Dijkstra's Algorithm

t_cell		*tcell_dup(t_cell *cur)
{
		t_cell	*prev;
		
		prev = (t_cell*)malloc(sizeof(t_cell));
		prev->distance = cur->distance;
		prev->is_visited = cur->is_visited;
		prev->name = cur->name;
		prev->neib = cur->neib;
		prev->size_neib = cur->size_neib;
		prev->prev = cur->prev;
		prev->next = cur->next;
		return (prev);
}

void		shortest_path(t_map *map)
{
	t_cell *cur;
	t_cell *prev;
	int		distance;
	int		i;
	
	distance = 0;
	i = 0;
	cur = map->arr_cell[map->start];
	//ft_printf("CHECK: %d\n", cur->size_neib);
	//cur = map->arr_cell[map->start]->neib[0];
	//ft_printf("CHECK: %d \n", cur->size_neib);
	cur->is_visited = 1;
	
	while (cur != map->arr_cell[map->end])
	{
		i = 0;
		distance++;
		prev = cur;
		ft_printf("PREV: %s\n", prev->name);
		while (i < prev->size_neib)
		{
			cur = prev->neib[i];
			if (cur == prev)
				i++;
			else if (!cur->is_visited)
			{
				if (visit_node(map, prev, cur, distance))
					break ;
			i++;
			}
		}
	}
}
/*
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
}*/