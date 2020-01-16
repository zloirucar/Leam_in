/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 12:43:48 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/16 13:22:54 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	drawline(t_draw *draw)
{
    float fx0;
    float y_begin;
    float y_target;
    float add_x;
    float add_y;
    float y_diff;
    int y_sign;

    fx0 = (float)draw->x1;
    add_x = (float)(draw->x2 - draw->x1);
    if (draw->y2 >= draw->y1)
    {
        y_diff = (float)(draw->y2 - draw->y1);
        y_sign = 1;
    }
    else
    {
        y_diff = (float)(draw->y1 - draw->y2);
        y_sign = -1;
    }
    if ((int)add_x < (int)y_diff)
    {
        add_x = add_x / y_diff;
        add_y = 1;
    }
    else
    {
        add_y = y_diff / add_x;
        add_x = 1;
    }
    y_begin = (float)draw->y1;
    y_target = (float)draw->y2;
    add_y *= y_sign;
    while ((int)fx0 < draw->x2 || ((int)y_begin < (int)y_target && y_sign == 1) ||
    ((int)y_begin > (int)y_target && y_sign == -1))
    {
        fx0 += add_x;
        y_begin += add_y;
        draw_square((int)fx0, (int)y_begin, 2, draw->vis);
    }
}