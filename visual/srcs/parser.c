/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 21:33:31 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/17 14:42:14 by oelaina          ###   ########.fr       */
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

t_solution		*init_solution(void)
{
	t_solution *tmp;

	if (!(tmp = (t_solution *)malloc(sizeof(t_solution))))
		exit(1);
	tmp->next = NULL;
	return (tmp);
}

void			check_links(char *line, t_map *map)
{
	if (check_char(line, '-') == 1)
		parse_links(map, line);
	else
		add_cell(map, line);
	printf_and_free(line);
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
		check_links(line, map);
	}
	free(line);
}
