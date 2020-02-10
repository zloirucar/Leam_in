/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimal_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 04:44:52 by skrabby           #+#    #+#             */
/*   Updated: 2020/02/10 18:44:19 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		count_finpaths(t_finpaths *lst)
{
	int			count;
	t_finpaths	*tmp;

	tmp = lst;
	count = 0;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

int		count_path(t_path *lst)
{
	int		count;
	t_path	*tmp;

	tmp = lst;
	count = 0;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (count > 0 ? count - 1 : 0);
}

int		check(t_finpaths *paths, int i)
{
	int			result;
	int			cursteps;
	int			j;
	t_finpaths	*cur;

	j = 0;
	result = 0;
	cur = paths;
	while (j++ < i)
		cur = cur->next;
	cursteps = count_path(cur->path);
	while (i > 0)
	{
		cur = paths;
		j = 0;
		i--;
		while (j++ < i)
			cur = cur->next;
		result += cursteps - count_path(cur->path);
	}
	return (result);
}

int		optimal_paths(t_finpaths *paths, int ants)
{
	int		i;
	int		opsize;
	int		size;

	i = 0;
	opsize = 0;
	size = count_finpaths(paths);
	if (size == 1)
		return (1);
	while (i < size)
	{
		if (ants > check(paths, i))
			opsize++;
		else
			break ;
		i++;
		ants--;
	}
	return (opsize);
}
