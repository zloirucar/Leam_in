/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:49:56 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/16 13:30:36 by oelaina          ###   ########.fr       */
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
	{
		free(draw);
        return (i);
	}
    drawline(draw);
	free(draw);
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
	free(draw);
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

t_antmove	*init_antmove(t_vis *v, t_map *map,
							int ant_index, char *room_name)
{
	t_antmove *am;

	if (!(am = (t_antmove *)malloc(sizeof(t_antmove))))
		exit (1);
	am->room_index = get_room_index(map, room_name);
	am->x0 = v->ants[ant_index]->visu_x;
	am->x1 = map->arr_cell[am->room_index]->x * 46 + v->padding_x + 9;
	am->y0 = v->ants[ant_index]->visu_y;
	am->y1 = map->arr_cell[am->room_index]->y * 46 + v->padding_y + 9;
	if (am->x0 == map->arr_cell[map->start]->x * 46 + v->padding_x + 9
	&& am->y0 == map->arr_cell[map->start]->y * 46 + v->padding_y + 9)
		v->start_room_ants -= 1;
	return (am);
}
void	set_diff_sign(t_antmove *am)
{
	if (am->x1 >= am->x0)
	{
		am->sign_x = 1;
		am->diffx = am->x1 - am->x0;
	}
	else
	{
		am->sign_x = -1;
		am->diffx = am->x0 - am->x1;
	}
	if (am->y1 >= am->y0)
	{
		am->sign_y = 1;
		am->diffy = am->y1 - am->y0;
	}
	else
	{
		am->sign_y = -1;
		am->diffy = am->y0 - am->y1;
	}
}

void	set_amspeed(t_vis *v, t_antmove *am)
{
	if (am->diffx >= am->diffy)
	{
		am->add_x = v->visu_speed;
		am->add_y = ((float)am->diffy /
		(float)am->diffx) * v->visu_speed;
	}
	else
	{
		am->add_y = v->visu_speed;
		am->add_x = ((float)am->diffx /
		(float)am->diffy) * v->visu_speed;
	}
}

void	mv_ants(t_vis *v, t_antmove *am, int a_i)
{
	v->ants[a_i]->carry_x += am->add_x;
	v->ants[a_i]->carry_y += am->add_y;
	if (v->ants[a_i]->carry_x >= v->visu_speed)
	{
		v->ants[a_i]->visu_x += v->visu_speed * am->sign_x;
		v->ants[a_i]->carry_x -= v->visu_speed;
	}
	if (v->ants[a_i]->carry_y >= v->visu_speed)
	{
		v->ants[a_i]->visu_y += v->visu_speed * am->sign_y;
		v->ants[a_i]->carry_y -= v->visu_speed;
	}
	if ((am->sign_x == 1 && v->ants[a_i]->visu_x > am->x1) ||
	(am->sign_x == -1 && v->ants[a_i]->visu_x < am->x1))
	{
		v->ants[a_i]->visu_x = am->x1;
		v->ants[a_i]->visu_y = am->y1;
	}
	else if ((am->sign_y == 1 && v->ants[a_i]->visu_y > am->y1)
	|| (am->sign_y == -1 && v->ants[a_i]->visu_y < am->y1))
	{
		v->ants[a_i]->visu_x = am->x1;
		v->ants[a_i]->visu_y = am->y1;
	}
}

int	visumove_ant(t_vis *v, t_map *map, int ant_index, char *room_name)
{
	t_antmove *am;

	am = init_antmove(v, map, ant_index, room_name);
	set_diff_sign(am);
	set_amspeed(v, am);
	
	if (am->x0 != am->x1 || am->y0 != am->y1)
	{
		mv_ants(v, am, ant_index);
		if (v->ants[ant_index]->visu_x ==
		map->arr_cell[map->end]->x * 46 + v->padding_x + 9
		&& v->ants[ant_index]->visu_y ==
		map->arr_cell[map->end]->y * 46 + v->padding_y + 9)
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
}