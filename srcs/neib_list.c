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

void	del_neib(t_map *map, t_neib *list,	char* name)
{
	t_neib *buf;
	t_neib *next_cell;
	t_neib *cur_cell;

	if (list == NULL)
		return;
	cur_cell = list;
	next_cell = cur_cell->next;
	while (cur_cell->next != NULL)
	{
		cur_cell = cur_cell->next;
	}
}