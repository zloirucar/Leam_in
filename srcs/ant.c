/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 17:46:31 by oelaina           #+#    #+#             */
/*   Updated: 2020/02/14 16:31:24 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static	void	set_last_cells(t_path **cur, t_path **end, t_path **prev)
{
	while ((*cur)->next)
		(*cur) = (*cur)->next;
	(*end) = (*cur);
	while ((*prev)->next != (*cur))
		(*prev) = (*prev)->next;
}

static	void	ant_drag(t_path **begin,
t_path **prev, t_path **cur, t_map **map)
{
	while ((*prev))
	{
		if ((*prev) == (*begin))
		{
			(*cur)->cell->ant = (*map)->ant_index;
			if ((*cur)->next == NULL)
				(*map)->count_end_ant += 1;
		}
		else
		{	
			if ((*prev)->cell->ant != 0)
			{
				if ((*cur)->next == NULL)
					(*map)->count_end_ant += 1;
			}
			(*cur)->cell->ant = (*prev)->cell->ant;
		}
		(*cur) = (*cur)->prev;
		(*prev) = (*prev)->prev;
	}
}

static	void	print_road(t_path **end,
t_map **map, int **newline, int *prev_end_ant)
{
	while ((*end))
	{
		if ((*end)->cell != (*map)->arr_cell[(*map)->start]->cell
		&& (*end)->cell->ant != 0)
		{
			if (!((*end)->cell == (*map)->arr_cell[(*map)->end]->cell
			&& (*end)->cell->ant == (*prev_end_ant)))
			{
				if (!**newline)
					ft_putchar(' ');
				else
					**newline = 0;
				ft_printpair((*end)->cell->ant, (*end)->cell->name);
			}
		}
		(*end) = (*end)->prev;
	}
	(*prev_end_ant) = (*map)->arr_cell[(*map)->end]->cell->ant;
}

void			move_ant(t_map *map,
t_finpaths *path, int ant_index, int *newline)
{
	t_path		*begin;
	t_path		*end;
	t_path		*cur;
	t_path		*prev;
	static int	prev_end_ant;

	begin = path->path;
	cur = begin;
	prev = begin;
	end = NULL;
	set_last_cells(&cur, &end, &prev);
	map->ant_index = ant_index;
	ant_drag(&begin, &prev, &cur, &map);
	print_road(&end, &map, &newline, &prev_end_ant);
}

void			ant_cross(t_map *map,
int ants, int opsize)
{
	int			count;
	int			maxop;

	map->newline = 1;
	count = 1;
	maxop = opsize;
	map->maxop = maxop;
	while (map->count_end_ant != map->count)
	{
		opsize = optimal_paths(map->paths, ants - count + 1);
		ant_cycle(map, opsize, maxop, &count);
		ft_putchar('\n');
		map->newline = 1;
	}
}
