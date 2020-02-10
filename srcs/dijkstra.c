/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 18:13:43 by oelaina           #+#    #+#             */
/*   Updated: 2020/02/10 18:45:09 by oelaina          ###   ########.fr       */
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

void			return_neib(t_map *map)
{
	t_finpaths	*tmp;
	t_path		*path;

	tmp = map->rev_paths;
	while (tmp)
	{
		path = tmp->path;
		while (path->next)
		{
			path->cell->next_neib =
			neib_addlast(path->cell->next_neib,
			path->next->cell->index);
			revert_weights(map, path->next->cell->next_neib,
			path->cell->name);
			path = path->next;
		}
		tmp = tmp->next;
	}
}
