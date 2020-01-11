/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 20:29:36 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/12 01:32:07 by skrabby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void		change_color(int r, int g, int b, t_vis *v)
{
	v->red = r;
	v->green = g;
	v->blue = b;
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
        ft_printf("YES\n");
    }
    ft_printf("y0: %d y1: %d y_diff: %f\n", y0, y1, y_diff);
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
    ft_printf("y_begin: %f y_target: %f addx: %f addy %f\n", y_begin, y_target, add_x, add_y);
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

void    print_rooms(t_map *map, t_vis *v)
{
    int padding_x;
    int padding_y;
    int count = 0;
    int coordx;
    int coordy;
    int x1;
    int x2;
    int y1;
    int y2;
    t_edge *edges;

    padding_x = 300;
    padding_y = 75;
    edges = map->edges;
    change_color(255, 255, 255, v);
    // edges
    while (edges)
    {
        if (edges->first_node->x * 46 + padding_x <
        edges->second_node->x * 46 + padding_x)
        {
            x1 = edges->first_node->x * 46 + padding_x + 18;
            x2 = edges->second_node->x * 46 + padding_x + 18;
            y1 = edges->first_node->y * 46 + padding_y + 18;
            y2 = edges->second_node->y * 46 + padding_y + 18;
        }
        else
        {
            x2 = edges->first_node->x * 46 + padding_x + 18;
            x1 = edges->second_node->x * 46 + padding_x + 18;
            y2 = edges->first_node->y * 46 + padding_y + 18;
            y1 = edges->second_node->y * 46 + padding_y + 18;
        }
        drawline(x1, y1, x2, y2, v);
        edges = edges->next;
    }
    change_color(255, 100, 255, v);
    
    //rooms
    while (count < map->size_arr)
    {
        coordx = map->arr_cell[count]->x * 46 + padding_x;
        coordy = map->arr_cell[count]->y * 46 + padding_y;
        draw_square(coordx, coordy, 36, v);
        count++;
    }
    //ants
    change_color (100, 255, 255, v);
    draw_square(map->arr_cell[map->start]->x * 46 + padding_x + 9,
    map->arr_cell[map->start]->y * 46 + padding_y + 9, 18, v);
    /*some code*/

    /*
    drawline(714, 305, 1036, 305, v);
    drawline(346, 305, 714, 305, v);
    drawline(1036, 213, 1358, 213, v);
    drawline(1036, 213, 1036, 305, v);
    drawline(714, 213, 1036, 397, v);
    drawline(714, 213, 1036, 213, v);
    drawline(1036, 305, 1036, 397, v);
    ft_printf("\n\n");*/
    //drawline(346, 305, 714, 213, v);
}

int ft_loop(t_vis *v)
{
    v->ret = mlx_get_data_addr(v->img, &(v->bits_per_pixel),
		&(v->size_line), &(v->endian));
    draw_background(v);
    print_rooms(v->map, v);
    mlx_put_image_to_window(v->mlx, v->win, v->img, 0, 0);
    mlx_destroy_image(v->mlx, v->img);
	v->img = mlx_new_image(v->mlx, WIDTH, HEIGHT);
    return (0);
}

t_vis	*set_var(void)
{
    t_vis *v;

    if (!(v = (t_vis*)malloc(sizeof(t_vis))))
        exit (1);
	v->red = 0;
	v->green = 0;
	v->blue = 0;
	v->map_created = 0;
	v->first_parse = 1;
    return (v);
}

int     main(void)
{
    t_map *map;
    t_vis *v;

    map = init_map();
    parser(map);
    v = set_var();
    v->map = map;
	v->mlx = mlx_init();
	v->win = mlx_new_window(v->mlx, WIDTH, HEIGHT, WINDOW_NAME);
	v->img = mlx_new_image(v->mlx, WIDTH, HEIGHT);
    //ft_loop(v, map);
    mlx_loop_hook(v->mlx, ft_loop, v);
    mlx_loop(v->mlx);
    ft_printf("\n");
    return (1);
}