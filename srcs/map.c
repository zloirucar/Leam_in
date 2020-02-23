/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 20:17:31 by oelaina           #+#    #+#             */
/*   Updated: 2020/02/14 18:04:02 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	*return_name(char *line, char c)
{
	int i;

	i = 0;
	while (line[i] != 0)
	{
		if (line[i] == c)
			break ;
		i++;
	}
	return (ft_strndup(line, i));
}

t_cell	*cell_addlast(t_map *map, char *line)
{
	t_cell	*tmp;
	t_cell	*list;
	char	*name;

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
		name = (return_name(line, ' '));
		check_name_list(&tmp, name);
		free(name);
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
	while (tmp->next)
		tmp = tmp->next;
	return (tmp->name);
}

void	parse_start_end(t_map *map, char *line)
{
	char *loc_line;

	loc_line = NULL;
	if (map->check_link == 1)
		error_msg();
	check_valid(&loc_line, &line);
	if (ft_strcmp(line, "##start") == 0)
	{
		map->cells = cell_addlast(map, loc_line);
		map->start_str = save_startend(map->cells);
		ft_printf("%s\n", line);
		ft_printf("%s\n", loc_line);
		free(loc_line);
		map->check_start = 1;
	}
	else if (ft_strcmp(line, "##end") == 0)
	{
		map->cells = cell_addlast(map, loc_line);
		map->end_str = save_startend(map->cells);
		ft_printf("%s\n", line);
		ft_printf("%s\n", loc_line);
		free(loc_line);
		map->check_end = 1;
	}
}

t_map	*init_map(void)
{
	t_map *map;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		exit(1);
	map->delete_path = NULL;
	map->rev_paths = NULL;
	map->paths = NULL;
	map->solution = NULL;
	map->cells = NULL;
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
	map->maxop = 0;
	return (map);
}
