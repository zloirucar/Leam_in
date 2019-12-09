/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 21:52:12 by oelaina           #+#    #+#             */
/*   Updated: 2019/12/09 21:41:13 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static	void	add_neib(t_cell *cell1, t_cell *cell2)
{
	inc_arr_cell(&(cell1->neib), &(cell1->size_neib));
	inc_arr_cell(&(cell2->neib), &(cell2->size_neib));
	cell1->neib[cell1->size_neib - 1] = cell2;
	cell2->neib[cell2->size_neib - 1] = cell1;
}

static	int		valid_link(char **arr)
{
	int i;

	i = 0;
	while (arr[i] != 0)
		i++;
	if (i > 2)
		return (0);
	else
		return (1);
}

static	int		check_names(t_map *map, char *name1, char *name2)
{
	int i;
	int	check1;
	int check2;

	i = 0;
	check1 = -1;
	check2 = -1;
	while (i < map->size_arr)
	{
		if (ft_strcmp(map->arr_cell[i]->name, name1) == 0)
			check1 = i;
		if (ft_strcmp(map->arr_cell[i]->name, name2) == 0)
			check2 = i;
		i++;
		if (check1 >=0  && check2 >= 0)
			break;
	}
	if (check1 >= 0 && check2 >= 0 && check1 != check2)
	{
		add_neib(map->arr_cell[check1], map->arr_cell[check2]);
		return (1);
	}
	else 
		return (0);
}

static	t_cell	*find_cell(t_map *map, char* line)
{
	char	**arr;
	int		i;

	i = 0;
	arr = ft_strsplit(line, "-");
	if (valid_link(arr) == 0 && check_names(map, arr[0], arr[1] == 0))
		return (NULL);
}

void	parse_links(t_map *map, char *line)
{
	if (map->check_cell == 1 && map->check_start == 1 && map->check_end == 1)
	{
		find_cell();
	}
	else
	{
		ft_fprintf(2, "ERROR");
		exit(1);
	}
	
}