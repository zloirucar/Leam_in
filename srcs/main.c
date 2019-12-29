/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:13:09 by oelaina           #+#    #+#             */
/*   Updated: 2019/12/29 14:04:15 by skrabby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	visual_struct(t_map *map)
{
	int size;

	size = 0;
	ft_printf("START %s %d %d\n", map->start->name, map->start->y, map->start->x);
	ft_printf("END %s %d %d\n", map->end->name, map->end->y, map->end->x);
	ft_printf("SIZE OF MAP_ARR %d\n", map->size_arr);
	ft_printf("COUNT = %d\n", map->count);
	while (size < map->size_arr)
	{
		ft_printf("%s %d %d\n", map->arr_cell[size]->name, map->arr_cell[size]->y, map->arr_cell[size]->x);
		size++;
	}
	int i = 0;
	ft_printf("SIZENEIB: %d", map->start->size_neib);
	while (i < map->start->size_neib)
	{
		ft_printf("NEIGHBOURS OF START: %s \n", map->start->neib[i]->name);
		i++;
	}
}

int	main(void)
{
	t_map *map;

	map = init_map();
	parse_map(map);
	visual_struct(map);
	return (0);
}