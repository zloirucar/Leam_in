/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solmove_pair.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 13:57:48 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/17 14:00:40 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

t_pair		*init_pair(void)
{
	t_pair *tmp;

	if (!(tmp = (t_pair *)malloc(sizeof(t_pair))))
		exit(1);
	tmp->next = NULL;
	tmp->ant_i = 0;
	tmp->room_name = NULL;
	tmp->isdone = 0;
	return (tmp);
}

t_pair		*pair_addlast(t_pair *list, int ant_i, char *room_name)
{
	t_pair *tmp;

	tmp = NULL;
	if (list == NULL)
	{
		list = init_pair();
		list->ant_i = ant_i;
		list->room_name = ft_strdup(room_name);
	}
	else
	{
		tmp = list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = init_pair();
		tmp = tmp->next;
		tmp->ant_i = ant_i;
		tmp->room_name = ft_strdup(room_name);
	}
	return (list);
}

t_solmove	*init_solmove(void)
{
	t_solmove *tmp;

	if (!(tmp = (t_solmove *)malloc(sizeof(t_solmove))))
		exit(1);
	tmp->next = NULL;
	return (tmp);
}

t_solmove	*solmove_addlast(t_solmove *list, t_pair *new)
{
	t_solmove *tmp;

	tmp = NULL;
	if (list == NULL)
	{
		list = init_solmove();
		list->pairlst = new;
	}
	else
	{
		tmp = list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = init_solmove();
		tmp = tmp->next;
		tmp->pairlst = new;
	}
	return (list);
}
