/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 12:29:08 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/17 19:00:00 by skrabby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

t_antmove	*init_antmove(t_vis *v, t_map *map,
							int ant_index, char *room_name)
{
	t_antmove *am;

	if (!(am = (t_antmove *)malloc(sizeof(t_antmove))))
		exit(1);
	am->room_index = search_cell(map, room_name);
	am->x0 = v->ants[ant_index]->visu_x;
	am->x1 = map->arr_cell[am->room_index]->cell->x * 46 + v->padding_x + 9;
	am->y0 = v->ants[ant_index]->visu_y;
	am->y1 = map->arr_cell[am->room_index]->cell->y * 46 + v->padding_y + 9;
	if (am->x0 == map->arr_cell[map->start]->cell->x * 46 + v->padding_x + 9
	&& am->y0 == map->arr_cell[map->start]->cell->y * 46 + v->padding_y + 9)
		v->start_room_ants -= 1;
	return (am);
}

void		mv_ants(t_vis *v, t_antmove *am, int a_i)
{
	v->ants[a_i]->carry_x += am->add_x;
	v->ants[a_i]->carry_y += am->add_y;
	if (v->ants[a_i]->carry_x >= v->visu_speed)
	{
		v->ants[a_i]->visu_x += v->visu_speed * am->sign_x;
		v->ants[a_i]->carry_x -= v->visu_speed;
	}
	if (v->ants[a_i]->carry_y >= v->visu_speed)
	{
		v->ants[a_i]->visu_y += v->visu_speed * am->sign_y;
		v->ants[a_i]->carry_y -= v->visu_speed;
	}
	if ((am->sign_x == 1 && v->ants[a_i]->visu_x > am->x1) ||
	(am->sign_x == -1 && v->ants[a_i]->visu_x < am->x1))
	{
		v->ants[a_i]->visu_x = am->x1;
		v->ants[a_i]->visu_y = am->y1;
	}
	else if ((am->sign_y == 1 && v->ants[a_i]->visu_y > am->y1)
	|| (am->sign_y == -1 && v->ants[a_i]->visu_y < am->y1))
	{
		v->ants[a_i]->visu_x = am->x1;
		v->ants[a_i]->visu_y = am->y1;
	}
}

int			visumove_ant(t_vis *v, t_map *map, int ant_index, char *room_name)
{
	t_antmove *am;

	am = init_antmove(v, map, ant_index, room_name);
	set_diff_sign(am);
	set_amspeed(v, am);
	if (am->x0 != am->x1 || am->y0 != am->y1)
	{
		mv_ants(v, am, ant_index);
		if (v->ants[ant_index]->visu_x ==
		map->arr_cell[map->end]->cell->x * 46 + v->padding_x + 9
		&& v->ants[ant_index]->visu_y ==
		map->arr_cell[map->end]->cell->y * 46 + v->padding_y + 9)
			v->end_room_ants += 1;
		return (0);
	}
	v->ants[ant_index]->carry_x = 0;
	v->ants[ant_index]->carry_y = 0;
	return (1);
}
