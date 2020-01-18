/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 19:14:11 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/18 21:34:46 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static	void	add_cell(t_map *map, char *line)
{
	parse_start_end(map, line);
	if (ft_strnstr(line, "#", 1))
		return ;
	map->cells = cell_addlast(map, line);
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
		if (map->count <= 0)
			error_msg();
		map->check_count = 1;
		return (0);
	}
	return (1);
}

static	void	printf_and_free(char *line)
{
	ft_putstr(line);
	ft_putchar('\n');
	free(line);
}

static	void	check_links(t_map *map, char *line)
{
	if (check_char(line, '-') == 1)
		parse_links(map, line);
	else
		add_cell(map, line);
	if (ft_strcmp(line, "##start") == 0
		|| ft_strcmp(line, "##end") == 0)
	{
		free(line);
		return ;
	}
	printf_and_free(line);
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
		if (ft_strncmp(line, "L", 1) == 0)
			error_msg();
		if (parse_count(map, line) == 0)
		{
			printf_and_free(line);
			continue;
		}
		check_links(map, line);
	}
	free(line);
}
