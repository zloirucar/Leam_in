/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:48:10 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/12 18:49:01 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void		draw_rectangle(int start_x, int start_y, t_vis *v)
{
	int		x;
	int		y;
	int		t;

	y = 0;
	t = 0;
	while (y < (v->h * 4))
	{
		x = 0;
		while (x < (v->len * 4))
		{
			v->ret[x + t +
			((start_y * v->width * 4) + (start_x * 4))] = v->blue;
			v->ret[x + t + 1 +
			((start_y * v->width * 4) + (start_x * 4))] = v->green;
			v->ret[x + t + 2 +
			((start_y * v->width * 4) + (start_x * 4))] = v->red;
			v->ret[x + t + 3 +
			((start_y * v->width * 4) + (start_x * 4))] = 0;
			x += 4;
		}
		y += 4;
		t += (v->width * 4);
	}
}

void		draw_square(int start_x, int start_y, int size, t_vis *v)
{
	int		i;
	int		i2;
	int		tmp;

	i2 = 0;
	tmp = 0;
	while (i2 < (size * 4))
	{
		i = 0;
		while (i < (size * 4))
		{
			v->ret[i + tmp + ((start_y * WIDTH * 4) +
					(start_x * 4))] = v->blue;
			v->ret[i + tmp + 1 + ((start_y * WIDTH * 4) +
					(start_x * 4))] = v->green;
			v->ret[i + tmp + 2 + ((start_y * WIDTH * 4) +
					(start_x * 4))] = v->red;
			v->ret[i + tmp + 3 + ((start_y * WIDTH * 4) +
					(start_x * 4))] = 0;
			i += 4;
		}
		i2 += 4;
		tmp += (WIDTH * 4);
	}
}

void		draw_background(t_vis *v)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	change_color(10, 20, 0, v);
	while (i < (HEIGHT * WIDTH * 4))
	{
		(v->ret)[i] = v->blue;
		(v->ret)[i + 1] = v->green;
		(v->ret)[i + 2] = v->red;
		(v->ret)[i + 3] = 0;
		i += 4;
		if (count < 22000)
			count++;
		else if (count == 22000 && v->blue <= 255)
		{
			count = 0;
			v->blue++;
            v->red++;
		}
	}
}

// x0 has to be < x1

void drawline(int x0, int y0, int x1, int y1, t_vis *v)
{
    float fx0;
    float y_begin;
    float y_target;
    float add_x;
    float add_y;
    float y_diff;
    int y_sign;

    fx0 = (float)x0;
    add_x = (float)(x1 - x0);
    if (y1 >= y0)
    {
        y_diff = (float)(y1 - y0);
        y_sign = 1;
    }
    else
    {
        y_diff = (float)(y0 - y1);
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
    y_begin = (float)y0;
    y_target = (float)y1;
    add_y *= y_sign;
    while ((int)fx0 < x1 || ((int)y_begin < (int)y_target && y_sign == 1) ||
    ((int)y_begin > (int)y_target && y_sign == -1))
    {
        fx0 += add_x;
        y_begin += add_y;
        draw_square((int)fx0, (int)y_begin, 2, v);
    }
    
    /*
	while(x<x1)
	{
		if(p>=0)
		{
			draw_square(x, y, 2, v);
			y=y+1;
			p=p+2*dy-2*dx;
		}
		else
		{
			draw_square(x, y, 2, v);
			p=p+2*dy;
		}
		x=x+1;
	}
    while (y < y1)
    {
        if(p>=0)
		{
			draw_square(x, y, 2, v);
			p=p+2*dx-2*dy;
		}
		else
		{
			draw_square(x, y, 2, v);
			p=p+2*dx;
		}
		y=y+1;
    }*/
}