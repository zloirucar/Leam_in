/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 19:14:11 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/07 20:07:52 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static	void	add_cell(t_map *map, char *line)
{
	parse_start_end(map, line);
	add_to_arr(map, line);
	map->count_cells++;
}

int				parse_count(t_map *map, char *line)
{
	int i;

	i = 0;
	if (map->check_count == 0)
	{
		while (line[i] != '\0')
		{
			if (ft_isdigit(line[i]) == 0)
				error_msg();
			i++;
		}
		map->count = ft_atoi(line);
		map->check_count = 1;
		return (0);
	}
	return (1);
}

static	void	printf_and_free(char *line)
{
	ft_printf("%s\n", line);
	free(line);
}

t_solution	*init_solution(void)
{
	t_solution *tmp;

	if (!(tmp = (t_solution *)malloc(sizeof(t_solution))))
		exit(1);
	tmp->next = NULL;
	return (tmp);
}

t_solution	*solution_addlast(t_solution *list, char *new_str)
{
	t_solution *tmp;
	char *new_turn;

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

void			parse_solution(t_map *map, char *line)
{
	free(line);
	while (get_next_line(0, &line))
	{
		map->solution = solution_addlast(map->solution, line);
		free(line);
	}
}

void			parse_map(t_map *map)
{
	char *line;

	line = NULL;
	while (get_next_line(0, &line))
	{
		if (ft_strncmp(line, "#", 1) == 0
		&& ft_strcmp(line, "##start") != 0
		&& ft_strcmp(line, "##end") != 0)
		{
			printf_and_free(line);
			continue;
		}
		if (!line[0])
		{
			parse_solution(map, line);
			return;
		}
		if (parse_count(map, line) == 0)
		{
			printf_and_free(line);
			continue;
		}
		if (check_char(line, '-') == 1)
			parse_links(map, line);
		else
			add_cell(map, line);
		if (!(ft_strstr(line, "##start") ||
		ft_strstr(line, "##end")))
			printf_and_free(line);
	}
	free (line);
}