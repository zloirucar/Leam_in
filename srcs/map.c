/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 20:17:31 by oelaina           #+#    #+#             */
/*   Updated: 2019/12/29 18:05:59 by skrabby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void parse_start_end(t_map *map, char *line)
{
	char *loc_line;

	if (ft_strstr(line, "##start"))
	{
		get_next_line(0, &loc_line);
		map->start = map->count_cells;
		add_to_arr(map, loc_line);
		free(loc_line);
		map->check_start = 1;
	}
	else if (ft_strstr(line, "##end"))
	{
		get_next_line(0, &loc_line);
		map->end = map->count_cells;
		add_to_arr(map, loc_line);
		free(loc_line);
		map->check_end = 1;
	}
}

void add_to_arr(t_map *map, char *line)
{
	if (ft_strnstr(line, "#", 1) || ft_strnstr(line, "L", 1))
		return;
	else
		inc_arr_cell(&(map->arr_cell), &(map->size_arr));
	map->arr_cell[map->size_arr - 1] = init_cell();
	set_cell(map->arr_cell[map->size_arr - 1], line);
	map->check_cell = 1;
}

t_map *init_map()
{
	t_map *map;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		exit(1);
	map->arr_cell = NULL;
	map->end = 0;
	map->start = 0;
	map->size_arr = 0;
	map->check_cell = 0;
	map->check_link = 0;
	map->check_start = 0;
	map->check_end = 0;
	map->count_cells = 0;
	return (map);
}

void parse_count(t_map *map, char *line)
{
	get_next_line(0, &line);
	map->count = ft_atoi(line);
	free(line);
}

void parse_map(t_map *map)
{
	char *line;

	line = NULL;
	parse_count(map, line);
	while (get_next_line(0, &line))
	{
		if (check_char(line, '-') == 1)
			parse_links(map, line);
		else
		{
			parse_start_end(map, line);
			add_to_arr(map, line);
			map->count_cells++;
		}
		free(line);
	}
}