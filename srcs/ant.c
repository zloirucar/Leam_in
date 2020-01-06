/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 17:46:31 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/06 18:47:34 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	move_ant(t_map *map, t_finpaths *path, int ant_index)
{
	t_path *begin;
	t_path *cur;
	t_path *prev;

	begin = path->path;
	cur = begin;
	prev = begin;
	begin->cell->ant = map->antsleft;
	while (cur->next)
		cur = cur->next;
	while (prev->next != cur)
		prev = prev->next;
	while (prev)
	{
		if (cur->next == NULL)
		{
			if (prev->cell->ant != 0)
				cur->cell->ant += 1;
			if (cur->cell->ant == map->count)
				map->crossed = 1;
		}
		else if (prev == begin)
			cur->cell->ant = ant_index;
		else
			cur->cell->ant = prev->cell->ant;
		cur = cur->prev;
		prev = prev->prev;
	}
}

void	ant_cross(t_map *map, int ants)
{
	int			count;
	t_finpaths	*begin;
	t_finpaths	*cur;

	begin = map->paths;
	cur = begin;
	count = 1;
	while (count <= ants || !map->crossed)
	{
		while (cur)
		{
			if (count <= ants)
			{
				move_ant(map, cur, count);
				count++;
			}
			else
				move_ant(map, cur, 0);
			cur = cur->next;
		}
		cur = begin;
	}
	printf("END: %d\n", map->arr_cell[map->end]->ant);
}
