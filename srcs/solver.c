/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 21:19:08 by skrabby           #+#    #+#             */
/*   Updated: 2020/01/17 18:07:24 by skrabby          ###   ########.fr       */
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
