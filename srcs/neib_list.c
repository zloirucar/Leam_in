/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neib_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 19:32:47 by oelaina           #+#    #+#             */
/*   Updated: 2019/12/30 22:11:44 by skrabby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_neib		*init_neib(void)
{
	t_neib	*tmp;

	if(!(tmp = (t_neib*)malloc(sizeof(t_neib))))
		exit(1);
	tmp->weight = 1;
	tmp->next = NULL;
	return (tmp);
}

t_neib	*neib_addlast(t_neib *alst, int index)
{
	t_neib	*tmp;

	tmp = NULL;
	if (alst == NULL)
	{
		alst = init_neib();
		alst->index = index;
	}
	else
	{
		tmp = alst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = init_neib();
		tmp = tmp->next;
		tmp->index = index;
	}
	return (alst);
}

void	del_neib(t_map *map, t_neib *list,	char* find_name)
{
//	t_neib *begin;
	t_neib *prev_cell;
	t_neib *cur_cell;

	if (list == NULL)
		return;
	cur_cell = list;
	while (cur_cell)
	{

		if (ft_strstr(map->arr_cell[cur_cell->index]->name, find_name))
		{
			printf("YESBLYAT, %s\n", map->arr_cell[cur_cell->index]->name);
			prev_cell->next = cur_cell->next;
			free(cur_cell);
		}
		prev_cell = cur_cell;
		cur_cell = cur_cell->next;
	}
}