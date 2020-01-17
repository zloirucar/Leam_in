/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_move_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 12:34:55 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/17 12:39:52 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

int		get_room_index(t_map *map, char *room_name)
{
	int i;

	i = 0;
	while (i < map->size_arr)
	{
		if (ft_strstr(map->arr_cell[i]->name, room_name))
			return (i);
		i++;
	}
	return (-1);
}

void	set_diff_sign(t_antmove *am)
{
	if (am->x1 >= am->x0)
	{
		am->sign_x = 1;
		am->diffx = am->x1 - am->x0;
	}
	else
	{
		am->sign_x = -1;
		am->diffx = am->x0 - am->x1;
	}
	if (am->y1 >= am->y0)
	{
		am->sign_y = 1;
		am->diffy = am->y1 - am->y0;
	}
	else
	{
		am->sign_y = -1;
		am->diffy = am->y0 - am->y1;
	}
}

void	set_amspeed(t_vis *v, t_antmove *am)
{
	if (am->diffx >= am->diffy)
	{
		am->add_x = v->visu_speed;
		am->add_y = ((float)am->diffy /
		(float)am->diffx) * v->visu_speed;
	}
	else
	{
		am->add_y = v->visu_speed;
		am->add_x = ((float)am->diffx /
		(float)am->diffy) * v->visu_speed;
	}
}
