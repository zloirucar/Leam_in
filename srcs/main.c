/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:13:09 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/07 20:20:56 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/*static void	visual_struct(t_map *map)
{
	ft_printf("START %s %d %d\n", map->arr_cell[map->start]->name, map->arr_cell[map->start]->y, map->arr_cell[map->start]->x);
	ft_printf("END %s %d %d\n", map->arr_cell[map->end]->name, map->arr_cell[map->end]->y, map->arr_cell[map->end]->x);
	ft_printf("SIZE OF MAP_ARR %d\n", map->size_arr);
	ft_printf("COUNT = %d\n", map->count);
	int size;

	size = 0;
	while (size < map->size_arr)
	{
		ft_printf("NAME: %s  DISTANCE: %d INDEX: %d\n", map->arr_cell[size]->name, map->arr_cell[size]->distance, map->arr_cell[size]->index);
		size++;
	}
	int i;
	i = 0;
	t_neib *tmp;
	
	//del_neib(map, map->arr_cell[4]->next_neib, "E");
	while (i < map->size_arr)
	{
		tmp = map->arr_cell[i]->next_neib;
		ft_printf("[NODE]: %s\n", map->arr_cell[i]->name);
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
		ft_printf("[EDGE] F: %s S: %s USED: %d\n", cur->first_node->name, cur->second_node->name, cur->used);
		cur = cur->next;
	}
	t_finpaths *temp;
	temp = map->paths;
	while (temp)
	{
		while (temp->path)
		{
			ft_printf("[SOLUTION PATH]: %s\n", temp->path->cell->name);
			temp->path = temp->path->next;
		}
		ft_printf("\n");
		temp = temp->next;
	}
}*/

int	main(void)
{
	t_map *map;

	map = init_map();
	parse_map(map);
	ft_printf("\n");
	bhandari_algo(map);
	//print_shortest(map->rev_paths->path);
	//print_shortest(map->rev_paths->next->path);
	//print_shortest(map->delete_path);
	ant_cross(map, map->count);
	//visual_struct(map);
	return (0);
}