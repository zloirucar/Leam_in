/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:49:56 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/16 13:19:39 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static  int    set_param(t_edge **edges, int padding_x, int padding_y, t_vis *v)
{
    int i;
	t_draw	*draw;

	i = 0;
	init_draw(&draw, v);
    if ((*edges)->first_node->x * 46 + padding_x <
        (*edges)->second_node->x * 46 + padding_x)
        {
            draw->x1 = (*edges)->first_node->x * 46 + padding_x + 18;
            draw->x2 = (*edges)->second_node->x * 46 + padding_x + 18;
            draw->y1 = (*edges)->first_node->y * 46 + padding_y + 18;
            draw->y2 = (*edges)->second_node->y * 46 + padding_y + 18;
            i = 1;
        }
    else
         return (i);
    drawline(draw);
    (*edges) = (*edges)->next;
    return (i);
}

static  void    set_another_param(t_edge **edges, int padding_x, int padding_y, t_vis *v)
{
    t_draw	*draw;

	init_draw(&draw, v);
    draw->x2 = (*edges)->first_node->x * 46 + padding_x + 18;
    draw->x1 = (*edges)->second_node->x * 46 + padding_x + 18;
    draw->y2 = (*edges)->first_node->y * 46 + padding_y + 18;
    draw->y1 = (*edges)->second_node->y * 46 + padding_y + 18;
    drawline(draw);
    (*edges) = (*edges)->next;
}


void    draw_edges(t_edge *edges, int padding_x, int padding_y, t_vis *v)
{
    while (edges)
    {
        if (set_param(&edges, padding_x, padding_y, v) == 0)
            set_another_param(&edges, padding_x, padding_y, v);
    }
}

void    draw_rooms(t_map *map, t_vis *v, int padding_x, int padding_y)
{
    int count;
    int coordx;
    int coordy;

    count = 0;
    while (count < map->size_arr)
    {
        coordx = map->arr_cell[count]->x * 46 + padding_x;
        coordy = map->arr_cell[count]->y * 46 + padding_y;
        if(count == map->start)
        {
            change_color(200, 90, 170, v);
            draw_square(coordx, coordy, 36, v);
            change_color(40, 180, 180, v);
            count++;
            continue ;
        }
        if(count == map->end)
        {
            change_color(50, 200, 130, v);
            draw_square(coordx, coordy, 36, v);
            change_color(40, 180, 180, v);
            count++;
            continue ;
        }
        draw_square(coordx, coordy, 36, v);
        count++;
    }
}

int	get_room_index(t_map *map, char *room_name)
{
	int i;

	i = 0;
	while (i < map->size_arr)
	{
		if (ft_strstr(map->arr_cell[i]->name, room_name))
			return (i);
		i++;
	}
	return (-1);
}

int	visumove_ant(t_vis *v, t_map *map, int ant_index, char *room_name)
{
	int x0;
	int x1;
	int y0;
	int y1;
	int diffx;
	int diffy;
	int sign_x;
	int sign_y;
	int room_index;
	float add_x;
	float add_y;

	room_index = get_room_index(map, room_name);
	x0 = v->ants[ant_index]->visu_x;
	x1 = map->arr_cell[room_index]->x * 46 + v->padding_x + 9;
	y0 = v->ants[ant_index]->visu_y;
	y1 = map->arr_cell[room_index]->y * 46 + v->padding_y + 9;
	if (x0 == map->arr_cell[map->start]->x * 46 + v->padding_x + 9
	&& y0 == map->arr_cell[map->start]->y * 46 + v->padding_y + 9)
		v->start_room_ants -= 1;
	if (x1 >= x0)
	{
		sign_x = 1;
		diffx = x1 - x0;
	}
	else
	{
		sign_x = -1;
		diffx = x0 - x1;
	}
	if (y1 >= y0)
	{
		sign_y = 1;
		diffy = y1 - y0;
	}
	else
	{
		sign_y = -1;
		diffy = y0 - y1;
	}
	if (diffx >= diffy)
	{
		add_x = v->visu_speed;
		add_y = ((float)diffy / (float)diffx) * v->visu_speed;
	}
	else
	{
		add_y = v->visu_speed;
		add_x = ((float)diffx / (float)diffy) * v->visu_speed;
	}
	//ft_printf("x:%d y:%d x1:%d y1:%d sign:%d\n", x0, y0, x1, y1, sign_x);
	if (x0 != x1 || y0 != y1)
	{
		v->ants[ant_index]->carry_x += add_x;
		v->ants[ant_index]->carry_y += add_y;
		if (v->ants[ant_index]->carry_x >= v->visu_speed)
		{
			v->ants[ant_index]->visu_x += v->visu_speed * sign_x;
			v->ants[ant_index]->carry_x -= v->visu_speed;
		}
		if (v->ants[ant_index]->carry_y >= v->visu_speed)
		{
			v->ants[ant_index]->visu_y += v->visu_speed * sign_y;
			v->ants[ant_index]->carry_y -= v->visu_speed;
		}
		if ((sign_x == 1 && v->ants[ant_index]->visu_x > x1) || (sign_x == -1 && v->ants[ant_index]->visu_x < x1))
		{
			v->ants[ant_index]->visu_x = x1;
			v->ants[ant_index]->visu_y = y1;
		}
		else if ((sign_y == 1 && v->ants[ant_index]->visu_y > y1) || (sign_y == -1 && v->ants[ant_index]->visu_y < y1))
		{
			v->ants[ant_index]->visu_x = x1;
			v->ants[ant_index]->visu_y = y1;
		}
		if (v->ants[ant_index]->visu_x == map->arr_cell[map->end]->x * 46 + v->padding_x + 9
		&& v->ants[ant_index]->visu_y == map->arr_cell[map->end]->y * 46 + v->padding_y + 9)
			v->end_room_ants += 1;
		return (0);
	}
	v->ants[ant_index]->carry_x = 0;
	v->ants[ant_index]->carry_y = 0;
	return (1);
}

#include <stdlib.h>
#include <time.h>

t_ant	**create_ants(t_map *map, t_vis *v)
{
	t_ant **ants;
	int i;

	i = 0;
	srand(time(NULL));
	if (!(ants = (t_ant**)malloc(sizeof(t_ant*) * map->count + 100)))
		exit (1);
	while (i < map->count)
	{
		if (!(ants[i] = (t_ant*)malloc(sizeof(t_ant) + 100)))
			exit (1);
		ants[i]->visu_x = map->arr_cell[map->start]->x * 46 + v->padding_x + 9;
    	ants[i]->visu_y = map->arr_cell[map->start]->y * 46 + v->padding_y + 9;
		ants[i]->index = i;
		ants[i]->carry_x = 0;
		ants[i]->carry_y = 0;
		ants[i]->color[0] = (rand() % (200 - 150 + 1)) + 150;
		ants[i]->color[1] = (rand() % (200 - 25 + 1)) + 25;
		ants[i]->color[2] = (rand() % (200 - 25 + 1)) + 25;
		i++;
	}
	return (ants);
}

void    print_rooms(t_map *map, t_vis *v)
{
    t_edge *edges;
	t_pair *tmp;
	int i;
	int countpair;
	int countdone;

	i = 0;
	countpair = 0;
	countdone = 0;
	tmp = v->solmove->pairlst;
    edges = map->edges;
    change_color(255, 255, 255, v);
    // edges
    draw_edges(edges, v->padding_x, v->padding_y, v);
    change_color(40, 180, 180, v);
    //rooms
    draw_rooms(map, v, v->padding_x, v->padding_y);
    //ants
	while(tmp)
	{
		if (visumove_ant(v, map, tmp->ant_i - 1, tmp->room_name))
			tmp->isdone = 1;
		if (tmp->isdone)
			countdone++;
		countpair++;
		tmp = tmp->next;
	}
	if (countpair == countdone && v->solmove->next)
		v->solmove = v->solmove->next;
	while (i < map->count)
	{
		change_color(v->ants[i]->color[0], v->ants[i]->color[1], v->ants[i]->color[2], v);
		draw_square(v->ants[i]->visu_x, v->ants[i]->visu_y, 18, v);
		i++;
	}
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