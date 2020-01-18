/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 18:13:43 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/17 18:15:26 by skrabby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static	void	set_param(t_cell **checklist,
t_cell **prev, t_cell **cur, t_map **map)
{
	(*checklist) = (*map)->arr_cell[(*map)->start]->cell;
	(*cur) = (*map)->arr_cell[(*map)->start]->cell;
	(*prev) = (*cur);
	(*cur)->is_visited = 1;
	(*cur)->distance = 0;
}

int				shortest_path(t_map *map)
{
	t_cell *cur;
	t_cell *prev;
	t_cell *checklist;
	t_neib *tmp;

	set_param(&checklist, &prev, &cur, &map);
	while (cur != map->arr_cell[map->end]->cell && checklist)
	{
		prev = checklist;
		tmp = prev->next_neib;
		while (tmp)
		{
			cur = map->arr_cell[tmp->index]->cell;
			if (!cur->is_visited)
			{
				checklist = checklist_addlast(checklist, cur);
				if (visit_node(map, prev, cur))
					return (1);
			}
			tmp = tmp->next;
		}
		checklist = checklist->sp_next;
	}
	return (0);
}

void			update_map(t_map *map)
{
	t_cell *tmp;

	tmp = map->cells;
	while (tmp)
	{
		tmp->distance = 0;
		tmp->is_visited = 0;
		tmp->prev = NULL;
		tmp->sp_next = NULL;
		tmp = tmp->next;
	}
}

void			print_shortest(t_path *list)
{
	t_path *tmp;

	if (!list)
		return ;
	tmp = list;
	while (tmp)
		tmp = tmp->next;
}

void			return_neib(t_map *map)
{
	t_finpaths *tmp;

	tmp = map->rev_paths;
	while (tmp)
	{
		while (tmp->path->next)
		{
			tmp->path->cell->next_neib =
			neib_addlast(tmp->path->cell->next_neib,
			tmp->path->next->cell->index);
			revert_weights(map, tmp->path->next->cell->next_neib,
			tmp->path->cell->name);
			tmp->path = tmp->path->next;
		}
		tmp = tmp->next;
	}
}
