/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 21:52:12 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/18 18:33:09 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static	int		add_neib(t_map *map, int check1, int check2)
{
	if (check1 >= 0 && check2 >= 0 && check1 != check2)
	{
		map->arr_cell[check1]->cell->next_neib =
		neib_addlast(map->arr_cell[check1]->cell->next_neib, check2);
		map->arr_cell[check2]->cell->next_neib =
		neib_addlast(map->arr_cell[check2]->cell->next_neib, check1);
		return (1);
	}
	else
		return (0);
}

static	int		valid_link(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != 0)
		i++;
	if (i != 2)
		return (0);
	else
		return (1);
}

static	int		check_names(t_map *map, char *name1, char *name2)
{
	unsigned long	check1;
	unsigned long	check2;

	check1 = search_cell(map, name1);
	check2 = search_cell(map, name2);
	return (add_neib(map, check1, check2));
}

static	int		find_cell(t_map *map, char *line)
{
	char **arr;

	arr = ft_strsplit(line, '-');
	if (valid_link(arr) == 0)
	{
		clear_2d_arr(arr);
		return (0);
	}
	else
	{
		if (check_names(map, arr[0], arr[1]) == 0)
			error_msg();
		clear_2d_arr(arr);
		return (1);
	}
}

void			parse_links(t_map *map, char *line)
{
	if (!map->check_hashtb)
	{
		create_hashtable(map);
		map->check_hashtb = 1;
	}
	if (map->check_start == 1 && map->check_end == 1)
	{
		if (find_cell(map, line) == 0)
			error_msg();
		map->check_link = 1;
	}
	else
		error_msg();
}
