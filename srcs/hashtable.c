/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 13:52:52 by skrabby           #+#    #+#             */
/*   Updated: 2020/01/17 17:03:47 by skrabby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

// DJB2 Hash Algorithm

unsigned long	get_hash(char *str, int rooms)
{

	unsigned long hash = 5381;
    int c;
    while ((c = *str++))
    	hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash % rooms * 100;
}

t_hashtable		*create_node(t_cell *cell, unsigned long h_i)
{
	t_hashtable	*node;

	if (!(node = (t_hashtable *)malloc(sizeof(t_hashtable))))
		exit (1);
	cell->index = h_i;
	node->cell = cell;
	node->key = cell->name;
	return (node);
}

unsigned long	search_cell(t_map *map, char *name)
{
	unsigned long hashIndex;

	hashIndex = get_hash(name, map->size_arr);
	while (map->arr_cell[hashIndex] == NULL ||
			ft_strcmp(map->arr_cell[hashIndex]->key, name))
	{
		hashIndex++;
		hashIndex %= map->size_arr * 100;
	}
	return (hashIndex);
}

void			fill_hashtable(t_map *map)
{
	t_cell			*tmp;
	unsigned long	hashIndex;

	tmp = map->cells;
	while (tmp)
	{
		hashIndex = get_hash(tmp->name, map->size_arr);
		while (map->arr_cell[hashIndex] != NULL) /* handle collision */
		{
			hashIndex++;
			hashIndex %= map->size_arr * 100;
		}
			map->arr_cell[hashIndex] = create_node(tmp, hashIndex);
		tmp = tmp->next;
	}
}

void			create_hashtable(t_map *map)
{
	int i;
	
	i = 0;
	if (!(map->arr_cell =(t_hashtable**)malloc(sizeof(t_hashtable*)
	* map->size_arr * 100)))
		exit (1);
	while (i < map->size_arr * 100)
	{
		map->arr_cell[i] = NULL;
		i++;
	}
	fill_hashtable(map);
}