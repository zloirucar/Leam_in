/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:13:09 by oelaina           #+#    #+#             */
/*   Updated: 2019/11/28 23:32:22 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static	void	set_cell(t_cell *cell, char *line)
{
	char	**arr;
	int		i;

	i = 0;
	arr = ft_strsplit(line, ' ');
	cell->name = arr[0];
	cell->y = ft_atoi(arr[1]);
	cell->x = ft_atoi(arr[2]);
	while (arr[i] != '\0')
	{
		free(arr[i]);
		i++;
	}
	free (arr[i]);
	free(arr);
}

static	t_cell	*init_cell()
{
	t_cell	*cell;

	if(!(cell = (t_cell *)malloc(sizeof(t_cell))))
		exit(1);
	cell->name = NULL;
	cell->neib = NULL;
	cell->size_neib = 0;
	return (cell);
}

static	void	parse_start_end(t_map *map, char *line)
{
	char	*loc_line;

	if (ft_strstr(line, "##start"))
	{
		get_next_line(0, loc_line);
		map->start = init_cell();
		set_cell(map->start, loc_line);
		free(loc_line);
	}
	else if (ft_strstr(line, "##end"))
	{
		get_next_line(0, loc_line);
		map->end = init_cell();
		set_cell(map->end, loc_line);
		free(loc_line);
	}
}


static	void mincr(t_cell **arr_cell)
{
	//TODO
}

static	void	add_to_arr(t_map *map, char *line)
{
	t_cell	**tmp;

	if (ft_strnstr(line, "#", 1) || ft_strnstr(line, "L", 1))
		return;
	else
	{
		if (map->arr_cell == NULL)
		{
			map->arr_cell = (t_cell **)malloc(sizeof(t_cell *));
			map->size_arr++;
		}
		else
		{
			//TODO
		}
		
	}
	
}

static	t_map	*init_map()
{
	t_map	*map;

	if (!(map = (t_map *)malloc(sizeof(t_map))))
		exit(1);
	map->arr_cell = NULL;
	map->end = NULL;
	map->start = NULL;
	map->size_arr = 0;
	return (map);
}

void	parse_map(t_map *map)
{
	char	*line;

	while (get_next_line(0, &line))
	{
		parse_start_end(map, line);
		add_to_arr(map, line);
		free(line);
	}
}

int	main(void)
{
	t_map *map;

	map = init_map();
	parse_map(map);
	return (0);
}