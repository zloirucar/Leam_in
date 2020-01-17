/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:13:09 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/17 14:48:54 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	main(void)
{
	t_map *map;

	map = init_map();
	parse_map(map);
	ft_printf("\n");
	bhandari_algo(map);
	if (map->paths)
		ant_cross(map, map->count);
	else
		error_msg();
	return (0);
}
