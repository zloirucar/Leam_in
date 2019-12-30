/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 21:19:08 by skrabby           #+#    #+#             */
/*   Updated: 2019/12/30 13:35:57 by skrabby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

//Bhandari Disjoint Path Finding

void	delete_shortest_path()
{
}


int	visit_nodes_neighbours(t_map *map, t_cell *this_node, int distance)
{
	int	i;
	i = 0;

	ft_printf("NAME : %s T: %d\n", this_node->name, this_node->size_neib);
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
		if (this_node->neib[i] == map->arr_cell[map->end])
			return (1);
		i++;
	}
	return (0);
}

int		visit_node(t_map *map, t_cell *prev_node, t_cell *new_node, int distance)
{
	ft_printf("S: %s, %d, %d, %d\n", new_node->name, new_node->y, new_node->x, new_node->size_neib);
	if ((distance < new_node->distance) || new_node->distance == 0)
	{
		new_node->prev = prev_node;
		new_node->distance = distance;
	}
	
	new_node->is_visited = 1;
	if (visit_nodes_neighbours(map, new_node, distance + 1))
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

t_cell		*checklist_addlast(t_cell *checklist, t_cell *new)
{
	t_cell *tmp;

	tmp = checklist;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (checklist);
}

void		printshort(t_map *map)
{
	t_cell *tmp;

	tmp = map->arr_cell[map->end];
	ft_printf("ROUTE: %s\n", tmp->name);
	while (tmp != map->arr_cell[map->start])
	{
		tmp = tmp->prev;
		ft_printf("ROUTE: %s\n", tmp->name);
	}
}

void		shortest_path(t_map *map)
{
	t_cell *cur;
	t_cell *prev;
	t_cell *checklist;

	int		distance;
	int		i;
	int		j;
	
	distance = 0;
	i = 0;
	j = 0;
	checklist = NULL;
	cur = map->arr_cell[map->start];
	prev = cur;
	cur->is_visited = 1;
	ft_printf("START: %s, %d, %d, %d, %p\n", cur->name, cur->x, cur->y, cur->is_visited, &(*cur));
	while (cur != map->arr_cell[map->end])
	{
		if (checklist == NULL)
			checklist = map->arr_cell[map->start];
		else 
			checklist = checklist->next;
		prev = checklist;
		ft_printf("PREV: %s\n", prev->name);
		while (i < prev->size_neib)
		{
			cur = prev->neib[i];
			ft_printf("CURR: %s, %d, %d, %d, %p\n", cur->name, cur->x, cur->y, cur->is_visited, &(*cur));
			if (!cur->is_visited)
			{
				checklist = checklist_addlast(checklist, cur);
				if (visit_node(map, prev, cur, distance))
				{
					printshort(map);
						return;
				}
			}
			i++;
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