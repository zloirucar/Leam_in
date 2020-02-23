/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:13:09 by oelaina           #+#    #+#             */
/*   Updated: 2020/02/14 20:16:41 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	main(void)
{
	t_map *map;

	map = init_map();
	parse_map(map);
	if (map->check_link == 0)
		error_msg();
	ft_putchar('\n');
	map->start = search_cell(map, map->start_str);
	map->end = search_cell(map, map->end_str);
	bhandari_algo(map);
	
	if (map->paths)
		ant_cross(map, map->count, optimal_paths(map->paths, map->count));
	else
		error_msg();
/*
	t_finpaths *tmp = map->paths;
	int sum = 0;
	int i = 0;
	while (tmp){
		//t_path *temp = tmp->path;
//		while(temp){
	if (i++ < map->maxop)
		sum += count_path(tmp->path);
			ft_printf("ROOMS: %d ", count_path(tmp->path));
//			temp = temp->next;
//		}
		tmp = tmp->next;
		ft_printf("\n");
	}
	ft_printf("SUM: %d\n", sum);*/
	clear_all(map);
	return (0);
}
