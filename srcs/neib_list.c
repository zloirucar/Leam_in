/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neib_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 19:32:47 by oelaina           #+#    #+#             */
/*   Updated: 2019/12/30 20:40:42 by oelaina          ###   ########.fr       */
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
		ft_printf("HERE2\n");
		tmp = alst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = init_neib();
		tmp = tmp->next;
		tmp->index = index;
	}
	return (alst);
}