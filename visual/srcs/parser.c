/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 21:33:31 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/16 13:03:28 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static	void	add_cell(t_map *map, char *line)
{
	parse_start_end(map, line);
	add_to_arr(map, line);
	map->count_cells++;
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

void			parser(t_map *map)
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
			return ;
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
		printf_and_free(line);
	}
	free (line);
}

/* x:714, y:305 ; x:1036, y:305
x:714, y:305 ; x:346, y:305
x:1358, y:213 ; x:1036, y:213
x:1036, y:305 ; x:1036, y:213
x:714, y:213 ; x:1036, y:397
x:1036, y:213 ; x:714, y:213
x:1036, y:305 ; x:1036, y:397
x:1036, y:397 ; x:1358, y:213
x:484, y:443 ; x:346, y:305
x:484, y:443 ; x:1036, y:397
x:484, y:443 ; x:1036, y:305
x:346, y:305 ; x:714, y:213
*/