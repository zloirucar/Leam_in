/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:13:09 by oelaina           #+#    #+#             */
/*   Updated: 2019/12/30 15:01:16 by skrabby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	visual_struct(t_map *map)
{
	int size;

	size = 0;
	ft_printf("START %s %d %d\n", map->arr_cell[map->start]->name, map->arr_cell[map->start]->y, map->arr_cell[map->start]->x);
	ft_printf("END %s %d %d\n", map->arr_cell[map->end]->name, map->arr_cell[map->end]->y, map->arr_cell[map->end]->x);
	ft_printf("SIZE OF MAP_ARR %d\n", map->size_arr);
	ft_printf("COUNT = %d\n", map->count);
	while (size < map->size_arr)
	{
		ft_printf("%s %d %d\n", map->arr_cell[size]->name, map->arr_cell[size]->y, map->arr_cell[size]->x);
		size++;
	}
	int i = 0;
	while (i < map->arr_cell[map->start]->neib[0]->size_neib)
	{
		ft_printf("NAME: %s\n", map->arr_cell[map->start]->neib[0]->name);
		ft_printf("NAME OF NEIB START: %s\n", map->arr_cell[map->start]->neib[0]->neib[i]->name);
		i++;
	}
}

int	main(void)
{
	t_map *map;

	map = init_map();
	parse_map(map);
	shortest_path(map);
	visual_struct(map);
	return (0);
}