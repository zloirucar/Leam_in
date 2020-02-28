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

t_neib *neibcpy(t_neib *neib)
{
	t_neib *dest;
	t_neib *src;

	src = neib;
	dest = NULL;
	while (src)
	{
		dest = neib_addlast(dest, src->index, 1);
		src = src->next;
	}
	return (dest);
}

t_cell	*cell_addlast_cpy(t_cell *cells, t_cell *src)
{
	t_cell	*tmp;
	
	if (cells == NULL)
	{
		cells = init_cell();
		cells->name = ft_strdup(src->name);
		cells->next_neib = neibcpy(src->next_neib);
		cells->index = src->index;
	}
	else
	{
		tmp = cells;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = init_cell();
		tmp = tmp->next;
		tmp->name = ft_strdup(src->name);
		tmp->next_neib = neibcpy(src->next_neib);
		tmp->index = src->index;
	}
	return (cells);
}

t_cell *copycells(t_cell *src)
{
	t_cell *tmp;
	t_cell *dest;

	dest = NULL;
	tmp = src;
	while (tmp)
	{
		dest = cell_addlast_cpy(dest, tmp);
		tmp = tmp->next;
	}
	return (dest);
} 

void reset_graph(t_map *map)
{
	t_path *tmp;
	t_cell *one;
	t_cell *two;
	t_finpaths *paths;
	t_path *path;

	paths = map->paths;
	tmp = map->delete_path;
	while (tmp)
	{
		one = map->arr_cell[search_cell(map, tmp->cell->name)]->cell;
		two = map->arr_cell[search_cell(map, tmp->next->cell->name)]->cell;
		one->next_neib =
		neib_addlast(one->next_neib, two->index, 1);
		two->next_neib =
		neib_addlast(two->next_neib, one->index, 1);
		tmp = tmp->next->next;
	}
	while (paths)
	{
		path = paths->path;
		while(path->next)
		{
			path->cell->next_neib = neib_addlast(path->cell->next_neib, path->next->cell->index, 1);
			path->next->cell->next_neib = neib_addlast(path->next->cell->next_neib, path->cell->index, 1);
			path = path->next;
		}
		paths = paths->next;
	}

}

void	reset_hashtable()
{

}

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
	map->cellscopy = copycells(map->cells);
	bhandari_algo(map);
	//update_map(map, NULL, map->cellscopy);
	reset_graph(map);
	map->maxop = optimal_paths(map->paths, map->count);
	clear_path(&(map->delete_path));
	clear_cell(&(map->cells));
	clear_list_finpath(&(map->paths));

	map->cells = copycells(map->cellscopy);
	clear_hashtable(map);
	create_hashtable(map, map->cells);
	bhandari_algo(map);
	if (map->paths)
		ant_cross(map, map->count, optimal_paths(map->paths, map->count));
	else
		error_msg();
	clear_all(map);
	return (0);
}
