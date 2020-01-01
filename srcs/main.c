/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:13:09 by oelaina           #+#    #+#             */
/*   Updated: 2019/12/30 21:46:37 by skrabby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	visual_struct(t_map *map)
{
	int size;

	size = 0;
	printf("START %s %d %d\n", map->arr_cell[map->start]->name, map->arr_cell[map->start]->y, map->arr_cell[map->start]->x);
	printf("END %s %d %d\n", map->arr_cell[map->end]->name, map->arr_cell[map->end]->y, map->arr_cell[map->end]->x);
	printf("SIZE OF MAP_ARR %d\n", map->size_arr);
	printf("COUNT = %d\n", map->count);
	while (size < map->size_arr)
	{
		printf("NAME: %s  DISTANCE: %d\n", map->arr_cell[size]->name, map->arr_cell[size]->distance);
		size++;
	}
	
	int i;
	i = 0;
	t_neib *tmp;
	
	//del_neib(map, map->arr_cell[4]->next_neib, "E");
	while (i < map->size_arr)
	{
		tmp = map->arr_cell[i]->next_neib;
		printf("ARRNAME: %s\n", map->arr_cell[i]->name);
		while (tmp)
		{
			ft_printf("NAME: %s\n", map->arr_cell[tmp->index]->name); 
			//map->arr_cell[tmp->index]->name
			tmp = tmp->next;
		}
		i++;
	}
}

int	main(void)
{
	t_map *map;

	map = init_map();
	parse_map(map);
	shortest_path(map);
	bhandari_algo(map);
	visual_struct(map);
	return (0);
}