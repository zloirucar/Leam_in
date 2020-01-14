/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 20:29:36 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/12 20:41:15 by oelaina          ###   ########.fr       */
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

void		draw_end_start(t_vis *v)
{
	char *s;
	char *nb;

	nb = ft_itoa(v->start_room_ants);
	s = ft_strjoin("START ROOM: ", nb);
	mlx_string_put(v->mlx, v->win, (WIDTH / 2) - 50,
	50 - 20, 0x0FFFFFF, s);
	free(s);
	free(nb);
	nb = ft_itoa(v->end_room_ants);
	s = ft_strjoin("END ROOM: ", nb);
	mlx_string_put(v->mlx, v->win, (WIDTH / 2) - 50,
	50 + 20, 0x0FFFFFF, s);
	free(s);
	free(nb);
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
	draw_end_start(v);
    return (0);
}

t_vis	*set_var(t_map *map)
{
    t_vis *v;

    if (!(v = (t_vis*)malloc(sizeof(t_vis))))
        exit (1);
	v->red = 0;
	v->green = 0;
	v->blue = 0;
	v->map_created = 0;
	v->first_parse = 1;
	v->padding_x = 300;
    v->padding_y = 75;
	v->start_room_ants = map->count;
	v->end_room_ants = 0;
    return (v);
}

int     main(void)
{
    t_map *map;
    t_vis *v;
   // t_graf *gr;
	t_ant **ants;

    map = init_map();
    parser(map);
    v = set_var(map);
    v->map = map;
	v->mlx = mlx_init();
	v->win = mlx_new_window(v->mlx, WIDTH, HEIGHT, WINDOW_NAME);
	v->img = mlx_new_image(v->mlx, WIDTH, HEIGHT);
    //ft_loop(v, map);
	ants = create_ants(map, v);
	v->ants = ants;
    mlx_loop_hook(v->mlx, ft_loop, v);
    mlx_loop(v->mlx);
    ft_printf("\n");
    return (1);
}