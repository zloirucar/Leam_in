/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:13:09 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/17 18:35:01 by skrabby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	main(void)
{
	t_map *map;

	map = init_map();
	parse_map(map);
	ft_putchar('\n');
	map->start = search_cell(map, map->start_str);
	map->end = search_cell(map, map->end_str);
	bhandari_algo(map);
	if (map->paths)
		ant_cross(map, map->count);
	else
		error_msg();
	return (0);
}
