/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:09:22 by oelaina           #+#    #+#             */
/*   Updated: 2019/11/28 23:14:54 by oelaina          ###   ########.fr       */
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
	t_cell				**arr_cell;
	t_cell				*start;
	t_cell				*end;

}						t_map;

void					parse_map(t_map *map);


#endif