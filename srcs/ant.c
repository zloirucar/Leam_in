/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 17:46:31 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/07 17:57:18 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static	void	set_last_cells(t_path **cur, t_path **end, t_path **prev)
{
	while ((*cur)->next)
		(*cur) = (*cur)->next; // last cell
	(*end) = (*cur);
	while ((*prev)->next != (*cur))
		(*prev) = (*prev)->next; // pre-last cell
}

static	void	ant_drag(t_path **begin, t_path **prev, t_path **cur, t_map **map)
{
	while ((*prev))
	{
		if ((*cur)->next == NULL)
		{
			if ((*prev)->cell->ant != 0)
				(*cur)->cell->ant += 1;
			if ((*cur)->cell->ant == (*map)->count)
				(*map)->crossed = 1;
		}
		else if ((*prev) == (*begin))
			(*cur)->cell->ant = (*map)->ant_index;
		else
			(*cur)->cell->ant = (*prev)->cell->ant;
		(*cur) = (*cur)->prev;
		(*prev) = (*prev)->prev;
	}
}

static	void	print_road(t_path **end, t_map **map, int **newline, int *prev_end_ant)
{
		while ((*end))
	{
		if ((*end)->cell != (*map)->arr_cell[(*map)->start] && (*end)->cell->ant != 0)
		{
			if (!((*end)->cell == (*map)->arr_cell[(*map)->end] && (*end)->cell->ant == (*prev_end_ant)))
			{
				if (!**newline)
					printf(" ");
				else
					**newline = 0;
				printf("L%d-%s", (*end)->cell->ant, (*end)->cell->name);
			}
		}
		(*end) = (*end)->prev;
	}
	(*prev_end_ant) = (*map)->arr_cell[(*map)->end]->ant;
	if ((*map)->antsleft > 0)
		(*map)->antsleft--;

}

void move_ant(t_map *map, t_finpaths *path, int ant_index, int *newline)
{
	t_path *begin;
	t_path *end;
	t_path *cur;
	t_path *prev;
	static int prev_end_ant;

	begin = path->path;
	cur = begin;
	prev = begin;
	begin->cell->ant = map->antsleft;
	end = NULL;
	set_last_cells(&cur, &end, &prev);
	map->ant_index = ant_index;
	ant_drag(&begin, &prev, &cur, &map);
	print_road(&end, &map, &newline, &prev_end_ant);
}

void ant_cross(t_map *map, int ants)
{
	int count;
	t_finpaths *begin;
	t_finpaths *cur;
	int newline;

	newline = 1;
	begin = map->paths;
	cur = begin;
	count = 1;
	while (count <= ants || !map->crossed)
	{
		while (cur)
		{
			if (count <= ants)
			{
				move_ant(map, cur, count, &newline);
				count++;
			}
			else
				move_ant(map, cur, 0, &newline);
			cur = cur->next;
		}
		printf("\n");
		cur = begin;
		newline = 1;
	}
}
