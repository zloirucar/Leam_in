/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:09:22 by oelaina           #+#    #+#             */
/*   Updated: 2019/12/08 22:01:18 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEAM_IN_H
# define LEAM_IN_H

#include "libft.h"

typedef	struct			s_cell
{
	char				*name;
	int					y;
	int					x;
	int					size_neib;
	struct	s_cell		**neib;
}						t_cell;

typedef	struct			s_map
{
	int					size_arr;
	int					count;
	int					check_cell;
	int					check_link;
	int					check_start;
	int					check_end;
	t_cell				**arr_cell;
	t_cell				*start;
	t_cell				*end;

}						t_map;

t_cell					*init_cell();
void					set_cell(t_cell *cell, char *line);
void					arr_cellcpy(t_cell **dest, t_cell **src, int size);
void					inc_arr_cell(t_cell ***arr_cell, int* size);
void					parse_start_end(t_map *map, char *line);
void					add_to_arr(t_map *map, char *line);
t_map					*init_map();
void					parse_map(t_map *map);
void					parse_count(t_map *map, char *line);
#endif