/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:13:09 by oelaina           #+#    #+#             */
/*   Updated: 2019/12/08 20:08:24 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static	void	set_cell(t_cell *cell, char *line)
{
	char	**arr;
	int		i;

	i = 0;
	arr = ft_strsplit(line, ' ');
	cell->name = ft_strdup(arr[0]);
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
	cell->size_neib = 0;
	return (cell);
}

static	void	parse_start_end(t_map *map, char *line)
{
	char	*loc_line;

	if (ft_strstr(line, "##start"))
	{
		get_next_line(0, &loc_line);
		map->start = init_cell();
		set_cell(map->start, loc_line);
		free(loc_line);
	}
	else if (ft_strstr(line, "##end"))
	{
		get_next_line(0, &loc_line);
		map->end = init_cell();
		set_cell(map->end, loc_line);
		free(loc_line);
	}
}


static	void	arr_cellcpy(t_cell **dest, t_cell **src, int size)
{
	int flag;

	flag = size;
	while (size >= 0)
	{
		dest[size] = src[size];
		//free (src[size]);
		size--;
	}
}

static	void	inc_arr_cell(t_cell ***arr_cell, int* size)
{
	t_cell	**buff;

	if (!(buff = (t_cell **)malloc(sizeof(t_cell *) * (*size))))
		exit (1);
	arr_cellcpy(buff, *arr_cell, *size - 1);
	if (*size <= 0)
		free (*arr_cell);
	if(!(*arr_cell = (t_cell **)malloc(sizeof(t_cell *) * (*size + 1))))
		exit (1);
	arr_cellcpy(*arr_cell, buff, *size - 1);
	if (*size <= 0)
		free (buff);
	(*size)++;
}

static	void	add_to_arr(t_map *map, char *line)
{
	if (ft_strnstr(line, "#", 1) || ft_strnstr(line, "L", 1))
		return;
	else
		inc_arr_cell(&(map->arr_cell), &(map->size_arr));
	map->arr_cell[map->size_arr - 1] = init_cell();
	set_cell(map->arr_cell[map->size_arr - 1], line);
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
		if (ft_strnstr(line, "-", 1))
		{
			free (line);
			break;
		}
		parse_start_end(map, line);
		add_to_arr(map, line);
		free(line);
	}
}

static void	visual_struct(t_map *map)
{
	int size;

	size = 0;
	ft_printf("START %s %d %d\n", map->start->name, map->start->y, map->start->x);
	ft_printf("END %s %d %d\n", map->start->name, map->end->y, map->end->x);
	ft_printf("SIZE OF MAP_ARR %d\n", map->size_arr);
	while (size < map->size_arr)
	{
		ft_printf("%s %d %d\n", map->arr_cell[size]->name, map->arr_cell[size]->y, map->arr_cell[size]->x);
		size++;
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