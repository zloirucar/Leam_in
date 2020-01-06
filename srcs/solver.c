/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 21:19:08 by skrabby           #+#    #+#             */
/*   Updated: 2020/01/02 19:53:18 by oelaina          ###   ########.fr       */
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

t_cell		*checklist_addlast(t_cell *checklist, t_cell *new)
{
	t_cell *tmp;

	tmp = checklist;
	if (tmp == NULL)
	{
		tmp = new;
		tmp->next = NULL;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		tmp->next->next = NULL;
	}
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

int		shortest_path(t_map *map)
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

void		update_map(t_map *map)
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
		return ;
	tmp = list;
	printf("ADSPOASDJASOPDJ\n");
	while (tmp)
	{
		printf("SHORT ROUTE: %s\n", tmp->cell->name);
		tmp = tmp->next;
	}
}

t_path		*init_path(void)
{
	t_path	*tmp;

	if(!(tmp = (t_path*)malloc(sizeof(t_path))))
		exit(1);
	tmp->next = NULL;
	tmp->prev = NULL;
	return (tmp);
}

t_path	*path_addlast(t_path *alst, t_cell *cell)
{
	t_path	*tmp;

	tmp = NULL;
	if (alst == NULL)
	{
		alst = init_path();
		alst->cell = cell;
	}
	else
	{
		tmp = alst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = init_path();
		tmp->next->cell = cell;
		//tmp->next->prev = tmp;
	}
	return (alst);
}

t_path		*revert_path(t_path *path)
{
	t_path *prev;
	t_path *curr;
	t_path *next;

	curr = path;
	prev = NULL;
	next = path;

	while (curr != NULL)
	{
		next = next->next;
		curr->next = prev;
		prev = curr;
		curr = next;
		prev->prev = curr;
	}
	return (prev);
}

void	return_neib(t_map *map)
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

void	delete_path(t_map *map)
{
	t_path *tmp;
	t_edge *unused;

	tmp = map->delete_path;
	unused = map->edges;
	while(tmp)
	{
		tmp->cell->next_neib = del_neib(map, tmp->cell->next_neib, tmp->next->cell->name);
		tmp->next->cell->next_neib = del_neib(map, tmp->next->cell->next_neib, tmp->cell->name);
		tmp = tmp->next->next;
	}
	while (unused)
	{
		unused->first_node->next_neib = del_neib(map, unused->first_node->next_neib, unused->second_node->name);
		unused->second_node->next_neib = del_neib(map, unused->second_node->next_neib, unused->first_node->name);
		unused = unused->next;
	}
}

t_finpaths		*init_finpaths(void)
{
	t_finpaths	*tmp;

	if(!(tmp = (t_finpaths*)malloc(sizeof(t_finpaths))))
		exit(1);
	tmp->next = NULL;
	return (tmp);
}

t_finpaths	*paths_addlast(t_finpaths *list, t_path *new_path)
{
	t_finpaths	*tmp;

	tmp = NULL;
	if (list == NULL)
	{
		list = init_finpaths();
		list->path = new_path;
	}
	else
	{
		tmp = list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = init_finpaths();
		tmp = tmp->next;
		tmp->path = new_path;
	}
	return (list);
}

//Bhandari Disjoint Path Finding

void		save_paths(t_map *map)
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

int			revert_weights(t_map *map, t_neib *list, char *find_name)
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

void		bellman_ford_weights(t_map *map)
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