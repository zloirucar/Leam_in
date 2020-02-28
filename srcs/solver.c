/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 21:19:08 by skrabby           #+#    #+#             */
/*   Updated: 2020/01/18 19:06:47 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_cell	*checklist_addlast(t_cell *checklist, t_cell *new)
{
	t_cell *tmp;

	tmp = checklist;
	if (tmp == NULL)
	{
		tmp = new;
		tmp->sp_next = NULL;
	}
	else
	{
		while (tmp->sp_next)
			tmp = tmp->sp_next;
		tmp->sp_next = new;
		tmp->sp_next->sp_next = NULL;
	}
	return (checklist);
}

void	save_paths(t_map *map)
{
	t_cell *cur;
	t_cell *prev;
	t_path *thispath;

	thispath = NULL;
	cur = map->arr_cell[map->end]->cell;
	while (cur != map->arr_cell[map->start]->cell)
	{
		prev = cur->prev;
		thispath = path_addlast(thispath, cur);
		prev->next_neib = del_neib(map, prev->next_neib, cur->name);
		cur->next_neib = del_neib(map, cur->next_neib, prev->name);
		cur = cur->prev;
	}
	thispath = path_addlast(thispath, cur);
	thispath = revert_path(thispath);
	map->paths = paths_addlast(map->paths, thispath);
}

int		revert_weights(t_map *map, t_cell *cur, t_cell *prev)
{
	t_neib *tmp;

	tmp = cur->next_neib;
	while (tmp)
	{
		if (!ft_strcmp(map->arr_cell[tmp->index]->cell->name, prev->name))
		{
			tmp->weight = -1;
			return (1);
		}
		tmp = tmp->next;
	}
	tmp = prev->next_neib;
	while (tmp)
	{
		if (!ft_strcmp(map->arr_cell[tmp->index]->cell->name, cur->name))
		{
			if (tmp->weight == -1)
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

void	bellman_ford_weights(t_map *map)
{
	t_cell *cur;
	t_cell *prev;
	t_path *thispath;
	t_cell *tmp;
	char   *find;

	thispath = NULL;
	cur = map->arr_cell[map->end]->cell;
	while (cur != map->arr_cell[map->start]->cell)
	{
		prev = cur->prev;
		thispath = path_addlast(thispath, cur);
		if (!(revert_weights(map, cur, prev)))
		{
			if (ft_strstr(cur->name, "(out)"))
			{
				find = ft_strndup(cur->name, ft_strlen(cur->name) - 5);
				tmp = map->arr_cell[search_cell(map, find)]->cell;
				free(find);
			}
			else
				tmp = cur; 
			map->delete_path = path_addlast(map->delete_path, tmp);
			if (ft_strstr(prev->name, "(out)"))
			{
				find = ft_strndup(cur->name, ft_strlen(cur->name) - 5);
				tmp = map->arr_cell[search_cell(map, find)]->cell;
				free(find);
			}
			else
				tmp = prev; 
			map->delete_path = path_addlast(map->delete_path, tmp);
		}
		prev->next_neib = del_neib(map, prev->next_neib, cur->name);
		cur = cur->prev;
	}
	thispath = path_addlast(thispath, cur);
	thispath = revert_path(thispath);
	map->rev_paths = paths_addlast(map->rev_paths, thispath);
}

t_neib *copyneib(t_map *map, t_cell *cur, t_cell *prev)
{
	t_neib *lst;
	t_neib *tmp;

	if (!cur->next_neib)
	return (NULL);
	lst = NULL;
	tmp = cur->next_neib;
	while (tmp)
	{
		if (map->arr_cell[tmp->index]->cell == prev)
			lst = neib_addlast(lst, cur->index, 0);
		else
			lst = neib_addlast(lst, tmp->index, 1);
		tmp = tmp->next;
	}
	return (lst);
}

t_cell *celldup(t_map *map, t_cell *cur, char *name, int hash_i)
{
	t_cell *dup;
	if (!(dup = (t_cell *)malloc(sizeof(t_cell))))
		exit(1);
    dup->name = name;
	dup->next = NULL;
	dup->sp_next = NULL;
	dup->prev = NULL;
	dup->index = hash_i;
	dup->distance = 0;
	dup->is_visited = 0;
	dup->ant = 0;
	dup->next_neib = copyneib(map, cur, cur->prev);
	return (dup);
}

void	adaptneib(t_map *map, t_neib *neib, t_cell *org, t_cell *new)
{
	t_neib *tmp;

	tmp = neib;
	if (!tmp)
		tmp = neib_addlast(tmp, new->index, 0);
	while (tmp)
	{
		if (!ft_strcmp(map->arr_cell[tmp->index]->cell->name, org->name))
		{
			tmp->index = new->index;
			break ;
		} 
		tmp = tmp->next;
	}
	tmp = org->next_neib;
	while (tmp)
	{
		if (ft_strcmp(map->arr_cell[tmp->index]->cell->name, org->prev->name) != 0)
			org->next_neib = del_neib(map, org->next_neib, map->arr_cell[tmp->index]->cell->name);
		tmp = tmp->next;
	}
}

t_cell *addnewcell(t_cell *list, t_cell *cell)
{
	t_cell *tmp;

	if (!list || !cell)
		return NULL;
	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = cell;
	return (list);
}

void	duplicate(t_map *map)
{
	t_cell			*cur;
	char			*dup;
	char			*tmp;

	unsigned long	hash_index;
	cur = map->arr_cell[map->end]->cell;
	dup = "(out)";
	while (cur->prev != map->arr_cell[map->start]->cell)
	{
		if (!ft_strstr(cur->prev->name, "(out)"))
		{
		tmp = ft_strjoin(cur->prev->name, dup);
		hash_index = get_hash(tmp, map->size_arr);
		while (map->arr_cell[hash_index] != NULL)
		{
			hash_index++;
			hash_index %= map->size_arr * 100;
		}
		map->arr_cell[hash_index] =
		create_node(celldup(map, cur->prev, tmp, hash_index), hash_index);
		adaptneib(map, cur->next_neib, cur->prev, map->arr_cell[hash_index]->cell);
		map->cells = addnewcell(map->cells, map->arr_cell[hash_index]->cell);
		}
		cur = cur->prev;
	}
}

void		checkcollision(t_map *map, int kpath)
{
	int i;

	i = 0;
	while (shortest_path(map) && i++ < kpath)
	{
		bellman_ford_weights(map);
		duplicate(map);
		update_map(map, NULL, map->cells);
	}
	update_map(map, NULL, map->cells);
}

void	bhandari_algo(t_map *map)
{
	checkcollision(map, map->maxop);
	clear_hashtable(map);
	create_hashtable(map, map->cellscopy);
	delete_path(map);
	while (shortest_path(map))
	{
		save_paths(map);
		update_map(map, map->paths, map->cellscopy);
	}
	update_map(map, NULL, map->cellscopy);
}
