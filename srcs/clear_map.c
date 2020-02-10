/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 18:37:23 by oelaina           #+#    #+#             */
/*   Updated: 2020/02/10 18:45:21 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	clear_all(t_map *map)
{
	clear_cell(&(map->cells));
	clear_list_finpath(&(map->paths));
	clear_list_finpath(&(map->rev_paths));
	clear_path(&(map->delete_path));
	clear_solution(&(map->solution));
	clear_edges(&(map->edges));
	clear_hashtable(map->arr_cell, map->size_hash);
	free(map);
}

void	clear_hashtable(t_hashtable **hash, int hash_size)
{
	int i;

	i = 0;
	while (i <= hash_size)
	{
		free(hash[i]->key);
		free(hash[i]);
		i++;
	}
	free(hash);
}

void	clear_edges(t_edge **edge)
{
	t_edge *tmp;
	t_edge *buf;

	tmp = *edge;
	while (tmp != NULL)
	{
		buf = tmp;
		tmp = tmp->next;
		free(buf);
	}
}

void	clear_solution(t_solution **solution)
{
	t_solution *tmp;
	t_solution *buf;

	tmp = *solution;
	while (tmp != NULL)
	{
		tmp = buf;
		tmp = tmp->next;
		free(buf->one_turn);
		free(buf);
		buf = NULL;
	}
}
