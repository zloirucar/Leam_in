/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 18:37:23 by oelaina           #+#    #+#             */
/*   Updated: 2020/02/14 14:43:56 by oelaina          ###   ########.fr       */
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
	clear_hashtable(map);
	free(map);
}

void	clear_hashtable(t_map *map)
{
	int i;

	i = 0;
	while (i < map->size_hash)
	{
		if (map->arr_cell[i] != NULL)
		{
		//	free(map->arr_cell[i]->key);
			free(map->arr_cell[i]);
			map->arr_cell[i] = NULL;
		}
		i++;
	}
	free(map->arr_cell);
	map->arr_cell = NULL;
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
