/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 13:52:52 by skrabby           #+#    #+#             */
/*   Updated: 2020/02/14 14:39:58 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

unsigned	long	get_hash(char *str, int rooms)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	while ((c = *str++))
		hash = ((hash << 5) + hash) + c;
	return (hash % rooms * 100);
}

t_hashtable			*create_node(t_cell *cell, unsigned long h_i)
{
	t_hashtable *node;

	if (!(node = (t_hashtable *)malloc(sizeof(t_hashtable))))
		exit(1);
	cell->index = h_i;
	node->cell = cell;
	node->key = cell->name;
	return (node);
}

unsigned	long	search_cell(t_map *map, char *name)
{
	unsigned long	hash_index;
	int				i;

	i = 0;
	hash_index = get_hash(name, map->size_arr);
	while (map->arr_cell[hash_index] == NULL ||
	ft_strcmp(map->arr_cell[hash_index]->key, name))
	{
		hash_index++;
		i++;
		if (i > map->size_arr * 100)
			error_msg();
		hash_index %= map->size_arr * 100;
	}
	return (hash_index);
}

void				fill_hashtable(t_map *map, t_cell *src)
{
	t_cell			*tmp;
	unsigned long	hash_index;

	tmp = src;
	while (tmp)
	{
		hash_index = get_hash(tmp->name, map->size_arr);
		while (map->arr_cell[hash_index] != NULL)
		{
			hash_index++;
			hash_index %= map->size_arr * 100;
		}
		map->arr_cell[hash_index] = create_node(tmp, hash_index);
		tmp = tmp->next;
	}
}

void				create_hashtable(t_map *map, t_cell *src)
{
	int i;

	i = 0;
	if (!(map->arr_cell = (t_hashtable **)
	malloc(sizeof(t_hashtable *) * map->size_arr * 100)))
		exit(1);
	map->size_hash = map->size_arr * 100;
	while (i < map->size_arr * 100)
	{
		map->arr_cell[i] = NULL;
		i++;
	}
	fill_hashtable(map, src);
}
