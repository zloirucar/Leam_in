/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 20:29:36 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/12 18:56:21 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void    draw_start_end(t_vis *v, t_map *map, int count)
{
    if (count == map->start)
    {
        change_color(0, 0, 0, v);

    }
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