/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 20:29:36 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/16 12:38:43 by oelaina          ###   ########.fr       */
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

void		draw_ant_index(t_vis *v)
{
	int i;

	i = 0;
	while (i < v->map->count)
	{
		if (i < v->map->count - v->start_room_ants &&
		(v->ants[i]->visu_x != v->map->arr_cell[v->map->end]->x * 46 + v->padding_x + 9 ||
		v->ants[i]->visu_y != v->map->arr_cell[v->map->end]->y * 46 + v->padding_y + 9))
		mlx_string_put(v->mlx, v->win, v->ants[i]->visu_x + 18,
		v->ants[i]->visu_y + 18, 0x0FFFFFF, ft_itoa(v->ants[i]->index));
		i++;
	}
}

void		draw_room_name(t_vis *v)
{
	int count;
    int coordx;
    int coordy;

    count = 0;
    while (count < v->map->size_arr)
    {
        coordx = v->map->arr_cell[count]->x * 46 + v->padding_x;
        coordy = v->map->arr_cell[count]->y * 46 + v->padding_y - 5;
        mlx_string_put(v->mlx, v->win, coordx, coordy, 0x0FFFFFF, v->map->arr_cell[count]->name);
        count++;
    }
}

void		draw_end_start(t_vis *v)
{
	char *s;
	char *nb;

	nb = ft_itoa(v->start_room_ants);
	s = ft_strjoin("START ROOM: ", nb);
	mlx_string_put(v->mlx, v->win, (WIDTH / 2) - 150,
	50 - 20, 0x0FFFFFF, s);
	free(s);
	free(nb);
	nb = ft_itoa(v->end_room_ants);
	s = ft_strjoin("END ROOM: ", nb);
	mlx_string_put(v->mlx, v->win, (WIDTH / 2) + 30,
	50 - 20, 0x0FFFFFF, s);
	free(s);
	free(nb);
}

t_pair	*init_pair(void)
{
	t_pair *tmp;

	if (!(tmp = (t_pair *)malloc(sizeof(t_pair))))
		exit(1);
	tmp->next = NULL;
	tmp->ant_i = 0;
	tmp->room_name = NULL;
	tmp->isdone = 0;
	return (tmp);
}

t_pair	*pair_addlast(t_pair *list, int ant_i, char *room_name)
{
	t_pair *tmp;

	tmp = NULL;
	if (list == NULL)
	{
		list = init_pair();
		list->ant_i = ant_i;
		list->room_name = ft_strdup(room_name);
	}
	else
	{
		tmp = list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = init_pair();
		tmp = tmp->next;
		tmp->ant_i = ant_i;
		tmp->room_name = ft_strdup(room_name);
	}
	return (list);
}

t_solmove	*init_solmove(void)
{
	t_solmove *tmp;

	if (!(tmp = (t_solmove *)malloc(sizeof(t_solmove))))
		exit(1);
	tmp->next = NULL;
	return (tmp);
}

t_solmove	*solmove_addlast(t_solmove *list, t_pair *new)
{
	t_solmove *tmp;

	tmp = NULL;
	if (list == NULL)
	{
		list = init_solmove();
		list->pairlst = new;
	}
	else
	{
		tmp = list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = init_solmove();
		tmp = tmp->next;
		tmp->pairlst = new;
	}
	return (list);
}

void	split_solution(t_map *map, t_vis *v)
{
	char **split;
	char **split_2;
	t_pair *pair;
	t_solution *tmp;
	int i;

	i = 0;
	v->solmove = NULL;
	tmp = map->solution;
	pair = NULL;
	while (tmp)
	{
		pair = NULL;
		split = ft_strsplit(tmp->one_turn, ' ');
		while (split[i])
		{
			split_2 = ft_strsplit(split[i], '-');
			pair = pair_addlast(pair, ft_atoi(split_2[0] + 1), split_2[1]);
			free(split_2[0]);
			free(split_2[1]);
			free(split_2);
			i++;
		}
		i = 0;
		while (split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
		v->solmove = solmove_addlast(v->solmove, pair);
		tmp = tmp->next;
		i = 0;
	}
	/*
	while (v->solmove)
	{
		while (v->solmove->pairlst)
		{
			ft_printf("%d : %s | ", v->solmove->pairlst->ant_i, v->solmove->pairlst->room_name);
			v->solmove->pairlst = v->solmove->pairlst->next;
		}
		ft_printf("\n");
		v->solmove = v->solmove->next;
	}
	*/
}

int ft_loop(t_vis *v)
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
			ft_printf("Usage(Visualizer): Room's X axis has to be <= 30, Y axis <= 16\n");
			ft_printf("Please, reconsider the map size\n");
			exit (1);
		}
		if (coordx < v->trim_x0)
			v->trim_x0 = coordx;
		if (coordx > v->trim_x1)
			v->trim_x1 = coordx + 36;
		if (coordy < v->trim_y0)
			v->trim_y0 = coordy;
		if (coordy > v->trim_y1)
			v->trim_y1 = coordy + 36;
			count++;
	}
	v->padding_x = (WIDTH / 2) - ((v->trim_x1 - v->trim_x0) / 2) - v->trim_x0;
	v->padding_y = (HEIGHT / 2) - ((v->trim_y1 - v->trim_y0) / 2) - v->trim_y0;
}

int			keyboard(int button, t_vis *v)
{
	int		i;

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

int     main(void)
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
    //ft_loop(v, map);
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