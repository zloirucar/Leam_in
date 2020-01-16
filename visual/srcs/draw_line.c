/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 12:43:48 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/16 13:41:28 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"


static void	init_drawline(t_drawline **drawline)
{
	if(!(*drawline = (t_drawline*)malloc(sizeof(t_drawline))))
		exit(1);
}

void	drawline(t_draw *draw)
{
	t_drawline *d;

	init_drawline(&d);
    d->fx0 = (float)draw->x1;
    d->add_x = (float)(draw->x2 - draw->x1);
    if (draw->y2 >= draw->y1)
    {
        d->y_diff = (float)(draw->y2 - draw->y1);
        d->y_sign = 1;
    }
    else
    {
        d->y_diff = (float)(draw->y1 - draw->y2);
        d->y_sign = -1;
    }
    if ((int)d->add_x < (int)d->y_diff)
    {
        d->add_x = d->add_x / d->y_diff;
        d->add_y = 1;
    }
    else
    {
        d->add_y = d->y_diff / d->add_x;
        d->add_x = 1;
    }
    d->y_begin = (float)draw->y1;
    d->y_target = (float)draw->y2;
    d->add_y *= d->y_sign;
    while ((int)d->fx0 < draw->x2 || ((int)d->y_begin < (int)d->y_target && d->y_sign == 1) ||
    ((int)d->y_begin > (int)d->y_target && d->y_sign == -1))
    {
       	d->fx0 += d->add_x;
        d->y_begin += d->add_y;
        draw_square((int)d->fx0, (int)d->y_begin, 2, draw->vis);
    }
	free(d);
}