/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:13:09 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/02 19:54:01 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	visual_struct(t_map *map)
{
	printf("START %s %d %d\n", map->arr_cell[map->start]->name, map->arr_cell[map->start]->y, map->arr_cell[map->start]->x);
	printf("END %s %d %d\n", map->arr_cell[map->end]->name, map->arr_cell[map->end]->y, map->arr_cell[map->end]->x);
	printf("SIZE OF MAP_ARR %d\n", map->size_arr);
	printf("COUNT = %d\n", map->count);
	int size;

	size = 0;
	while (size < map->size_arr)
	{
		printf("NAME: %s  DISTANCE: %d INDEX: %d\n", map->arr_cell[size]->name, map->arr_cell[size]->distance, map->arr_cell[size]->index);
		size++;
	}
	int i;
	i = 0;
	t_neib *tmp;
	
	//del_neib(map, map->arr_cell[4]->next_neib, "E");
	while (i < map->size_arr)
	{
		tmp = map->arr_cell[i]->next_neib;
		printf("[NODE]: %s\n", map->arr_cell[i]->name);
		while (tmp)
		{
			ft_printf("NEIB: %s\n", map->arr_cell[tmp->index]->name); 
			//map->arr_cell[tmp->index]->name
			tmp = tmp->next;
		}
		i++;
	}
	t_edge *cur;
	cur = map->edges;
	while (cur)
	{
		printf("[EDGE] F: %s S: %s USED: %d\n", cur->first_node->name, cur->second_node->name, cur->used);
		cur = cur->next;
	}
	t_finpaths *temp;
	temp = map->paths;
	while (temp)
	{
		while (temp->path)
		{
			printf("[SOLUTION PATH]: %s\n", temp->path->cell->name);
			temp->path = temp->path->next;
		}
		printf("\n");
		temp = temp->next;
	}
}

t_edge		*remove_used_edge(t_map *map, char *fnode_name, char *snode_name)
{
	t_edge *prev_cell;
	t_edge *cur_cell;
	t_edge *begin;
	
	if (map->edges == NULL)
		return NULL;
	begin = map->edges;
	cur_cell = map->edges;
	prev_cell = NULL;
	while (cur_cell)
	{
		if ((ft_strstr(cur_cell->first_node->name, fnode_name) && 
		(ft_strstr(cur_cell->second_node->name, snode_name))) || 
		((ft_strstr(cur_cell->first_node->name, snode_name) && 
		(ft_strstr(cur_cell->second_node->name, fnode_name)))))
		{
			printf("NASHEL!!!, %s %s\n", cur_cell->first_node->name, cur_cell->second_node->name);
			if (prev_cell)
				prev_cell->next = cur_cell->next;
			else
				begin = cur_cell->next;
			free(cur_cell);
			return (begin);
		}
		prev_cell = cur_cell;
		cur_cell = cur_cell->next;
	}
	return (begin);
}

t_edge		*init_edge(void)
{
	t_edge	*tmp;

	if(!(tmp = (t_edge*)malloc(sizeof(t_edge))))
		exit(1);
	tmp->used = 0;
	tmp->next = NULL;
	return (tmp);
}

t_edge	*edge_addlast(t_edge *list, t_cell *fnode, t_cell *snode)
{
	t_edge	*tmp;

	tmp = NULL;
	if (list == NULL)
	{
		list = init_edge();
		list->first_node = fnode;
		list->second_node = snode;
	}
	else
	{
		tmp = list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = init_edge();
		tmp = tmp->next;
		tmp->first_node = fnode;
		tmp->second_node = snode;
	}
	return (list);
}

int	main(void)
{
	t_map *map;

	map = init_map();
	parse_map(map);
	bhandari_algo(map);
	//print_shortest(map->rev_paths->path);
	//print_shortest(map->rev_paths->next->path);
	//print_shortest(map->delete_path);
	visual_struct(map);
	return (0);
}