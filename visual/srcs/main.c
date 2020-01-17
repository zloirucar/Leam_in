/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 20:29:36 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/17 14:36:03 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

int		ft_loop(t_vis *v)
{
	if (!v->pause)
	{
		v->ret = mlx_get_data_addr(v->img, &(v->bits_per_pixel),
					&(v->size_line), &(v->endian));
		draw_background(v);
		print_rooms(v->map, v);
		mlx_put_image_to_window(v->mlx, v->win, v->img, 0, 0);
		mlx_destroy_image(v->mlx, v->img);
		v->img = mlx_new_image(v->mlx, WIDTH, HEIGHT);
		draw_end_start(v);
		draw_ant_index(v);
		draw_room_name(v);
	}
	else
		mlx_string_put(v->mlx, v->win, (WIDTH / 2) - 30,
		HEIGHT / 2, 0x0FFFFFF, "PAUSE");
	return (0);
}

void	get_coord(int *coordx, int *coordy, t_vis *v)
{
	if (*coordx < v->trim_x0)
		v->trim_x0 = *coordx;
	if (*coordx > v->trim_x1)
		v->trim_x1 = *coordx + 36;
	if (*coordy < v->trim_y0)
		v->trim_y0 = *coordy;
	if (*coordy > v->trim_y1)
		v->trim_y1 = *coordy + 36;
}

void	calculate_padding(t_map *map, t_vis *v)
{
	int coordx;
	int coordy;
	int count;

	count = 0;
	while (count < map->size_arr)
	{
		coordx = map->arr_cell[count]->x * 46 + v->padding_x;
		coordy = map->arr_cell[count]->y * 46 + v->padding_y;
		if (coordx > 1400 || coordy > 750)
		{
			ft_printf("Usage(Visualizer): \
			Room's X axis has to be <= 30, Y axis <= 16\n");
			ft_printf("Please, reconsider the map size\n");
			exit(1);
		}
		get_coord(&coordx, &coordy, v);
		count++;
	}
	v->padding_x = (WIDTH / 2) - ((v->trim_x1 - v->trim_x0) / 2) - v->trim_x0;
	v->padding_y = (HEIGHT / 2) - ((v->trim_y1 - v->trim_y0) / 2) - v->trim_y0;
}

int		keyboard(int button, t_vis *v)
{
	int i;

	i = 1;
	if (button == SPACE)
	{
		if (!v->pause)
			v->pause = 1;
		else
			v->pause = 0;
	}
	else if (button == ESC)
		exit(1);
	return (0);
}

int		main(void)
{
	t_map *map;
	t_vis *v;
	t_ant **ants;

	map = init_map();
	parser(map);
	v = set_var(map);
	v->map = map;
	v->mlx = mlx_init();
	v->win = mlx_new_window(v->mlx, WIDTH, HEIGHT, WINDOW_NAME);
	v->img = mlx_new_image(v->mlx, WIDTH, HEIGHT);
	calculate_padding(map, v);
	ants = create_ants(map, v);
	v->ants = ants;
	split_solution(map, v);
	mlx_hook(v->win, 2, 2, keyboard, v);
	mlx_loop_hook(v->mlx, ft_loop, v);
	mlx_loop(v->mlx);
	ft_printf("\n");
	return (1);
}
