/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solution.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 14:15:21 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/17 14:37:45 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

t_solution	*solution_addlast(t_solution *list, char *new_str)
{
	t_solution	*tmp;
	char		*new_turn;

	new_turn = ft_strdup(new_str);
	tmp = NULL;
	if (list == NULL)
	{
		list = init_solution();
		list->one_turn = new_turn;
	}
	else
	{
		tmp = list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = init_solution();
		tmp = tmp->next;
		tmp->one_turn = new_turn;
	}
	return (list);
}

void		parse_solution(t_map *map, char *line)
{
	free(line);
	while (get_next_line(0, &line))
	{
		map->solution = solution_addlast(map->solution, line);
		free(line);
	}
}

void		get_pair(char **split, t_pair **pair, int *i)
{
	char **split_2;

	while (split[*i])
	{
		split_2 = ft_strsplit(split[*i], '-');
		*pair = pair_addlast(*pair, ft_atoi(split_2[0] + 1), split_2[1]);
		free(split_2[0]);
		free(split_2[1]);
		free(split_2);
		(*i)++;
	}
}

void		split_solution(t_map *map, t_vis *v)
{
	char		**split;
	t_pair		*pair;
	t_solution	*tmp;
	int			i;

	i = 0;
	v->solmove = NULL;
	tmp = map->solution;
	pair = NULL;
	while (tmp)
	{
		pair = NULL;
		split = ft_strsplit(tmp->one_turn, ' ');
		get_pair(split, &pair, &i);
		i = 0;
		while (split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
		v->solmove = solmove_addlast(v->solmove, pair);
		tmp = tmp->next;
		i = 0;
	}
}
