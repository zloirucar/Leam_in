/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 20:17:31 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/17 18:16:46 by skrabby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_cell			*cell_addlast(t_map *map, char *line)
{
	t_cell	*tmp;
	t_cell	*list;
	
	list = map->cells;
	tmp = NULL;
	if (list == NULL)
	{
		list = init_cell();
		set_cell(list, line);
	}
	else
	{
		tmp = list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = init_cell();
		tmp = tmp->next;
		set_cell(tmp, line);
	}
	map->size_arr += 1;
	return (list);
}

char	*save_startend(t_cell *begin)
{
	t_cell *tmp;

	tmp = begin;
	while(tmp->next)
		tmp = tmp->next;
	return (tmp->name);
}

void	parse_start_end(t_map *map, char *line)
{
	char *loc_line;

	if (map->check_link == 1)
		error_msg();
	if (ft_strcmp(line, "##start") == 0)
	{
		ft_printf("%s\n", line);
		get_next_line(0, &loc_line);
		map->cells = cell_addlast(map, loc_line);
		map->start_str = save_startend(map->cells);
		ft_printf("%s\n", loc_line);
		free(loc_line);
		map->check_start = 1;
	}
	else if (ft_strcmp(line, "##end") == 0)
	{
		ft_printf("%s\n", line);
		get_next_line(0, &loc_line);
		map->cells = cell_addlast(map, loc_line);
		map->end_str = save_startend(map->cells);
		ft_printf("%s\n", loc_line);
		free(loc_line);
		map->check_end = 1;
	}
}
/*
void	add_to_arr(t_map *map, char *line)
{
	if (ft_strnstr(line, "#", 1))
		return ;
	else
		inc_arr_cell(&(map->arr_cell), &(map->size_arr));
	map->arr_cell[map->size_arr - 1] = init_cell();
	set_cell(map->arr_cell[map->size_arr - 1], line, map->size_arr - 1);
	map->check_cell = 1;
}
*/
t_map	*init_map(void)
{
	t_map *map;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		exit(1);
//	map->arr_cell = NULL;
	map->delete_path = NULL;
	map->rev_paths = NULL;
	map->paths = NULL;
	map->edges = NULL;
	map->solution = NULL;
	map->cells = NULL;
	map->crossed = 0;
	map->count_end_ant = 0;
	map->end = 0;
	map->start = 0;
	map->size_arr = 0;
	map->check_cell = 0;
	map->check_link = 0;
	map->check_start = 0;
	map->check_end = 0;
	map->count_cells = 0;
	map->check_count = 0;
	map->check_hashtb = 0;
	return (map);
}
