/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:55:14 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/17 15:02:04 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void		change_color(int r, int g, int b, t_vis *v)
{
	v->red = r;
	v->green = g;
	v->blue = b;
}

void		init_printrooms(t_printrooms **p)
{
	if (!(*p = (t_printrooms*)malloc(sizeof(t_printrooms))))
		exit(1);
	(*p)->countdone = 0;
	(*p)->i = 0;
	(*p)->countpair = 0;
}

t_vis		*set_var(t_map *map)
{
	t_vis *v;

	if (!(v = (t_vis *)malloc(sizeof(t_vis))))
		exit(1);
	v->red = 0;
	v->green = 0;
	v->blue = 0;
	v->map_created = 0;
	v->first_parse = 1;
	v->padding_x = 0;
	v->padding_y = 0;
	v->start_room_ants = map->count;
	v->end_room_ants = 0;
	v->visu_speed = 15;
	v->pause = 0;
	v->trim_x0 = WIDTH;
	v->trim_x1 = 0;
	v->trim_y0 = HEIGHT;
	v->trim_y1 = 0;
	return (v);
}
