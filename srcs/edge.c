/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 17:48:51 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/07 19:44:13 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static	void	set_param(t_edge **begin,
t_edge **cur_cell, t_edge **prev_cell, t_map **map)
{
	*begin = (*map)->edges;
	*cur_cell = (*map)->edges;
	*prev_cell = NULL;
}

t_edge			*remove_used_edge(t_map *map,
char *fnode_name, char *snode_name)
{
	t_edge *prev_cell;
	t_edge *cur_cell;
	t_edge *begin;

	if (map->edges == NULL)
		return (NULL);
	set_param(&begin, &cur_cell, &prev_cell, &map);
	while (cur_cell)
	{
		if ((ft_strstr(cur_cell->first_node->name, fnode_name) &&
		(ft_strstr(cur_cell->second_node->name, snode_name))) ||
		((ft_strstr(cur_cell->first_node->name, snode_name) &&
		(ft_strstr(cur_cell->second_node->name, fnode_name)))))
		{
			if (prev_cell)
				prev_cell->next = cur_cell->next;
			else
				begin = cur_cell->next;
			free(cur_cell);
			return (begin);
		}
		prev_cell = cur_cell;
		cur_cell = cur_cell->next;
	}
	return (begin);
}

t_edge			*init_edge(void)
{
	t_edge	*tmp;

	if (!(tmp = (t_edge*)malloc(sizeof(t_edge))))
		exit(1);
	tmp->used = 0;
	tmp->next = NULL;
	return (tmp);
}

t_edge			*edge_addlast(t_edge *list, t_cell *fnode, t_cell *snode)
{
	t_edge	*tmp;

	tmp = NULL;
	if (list == NULL)
	{
		list = init_edge();
		list->first_node = fnode;
		list->second_node = snode;
	}
	else
	{
		tmp = list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = init_edge();
		tmp = tmp->next;
		tmp->first_node = fnode;
		tmp->second_node = snode;
	}
	return (list);
}
