/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:48:10 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/17 15:24:04 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void		init_draw(t_draw **draw, t_vis *vis)
{
	if (!(*draw = (t_draw*)malloc(sizeof(t_draw))))
		exit(1);
	(*draw)->vis = vis;
	(*draw)->x1 = 0;
	(*draw)->x2 = 0;
	(*draw)->y1 = 0;
	(*draw)->y2 = 0;
}

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
	change_color(1, 5, 10, v);
	while (i < (HEIGHT * WIDTH * 4))
	{
		(v->ret)[i] = v->blue;
		(v->ret)[i + 1] = v->green;
		(v->ret)[i + 2] = v->red;
		(v->ret)[i + 3] = 0;
		i += 4;
		if (count < 30000)
			count++;
		else if (count == 30000 && v->blue <= 255 && v->green <= 255)
		{
			count = 0;
			v->blue++;
			v->green++;
		}
	}
}
