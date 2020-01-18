/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:49:56 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/18 18:39:17 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	return_color(int coordx, int coordy, t_vis *vis, t_cell **tmp)
{
	draw_square(coordx, coordy, 36, vis);
	change_color(40, 180, 180, vis);
	(*tmp) = (*tmp)->next;
}

void	draw_rooms(t_map *map, t_vis *v, int padding_x, int padding_y)
{
	int		coordx;
	int		coordy;
	t_cell	*tmp;

	tmp = map->cells;
	while (tmp)
	{
		coordx = tmp->x * 46 + padding_x;
		coordy = tmp->y * 46 + padding_y;
		if (tmp->index == map->start)
		{
			change_color(200, 90, 170, v);
			return_color(coordx, coordy, v, &tmp);
			continue;
		}
		if (tmp->index == map->end)
		{
			change_color(50, 200, 130, v);
			return_color(coordx, coordy, v, &tmp);
			continue;
		}
		draw_square(coordx, coordy, 36, v);
		tmp = tmp->next;
	}
}

t_ant	**create_ants(t_map *map, t_vis *v)
{
	t_ant	**ants;
	int		i;

	i = 0;
	srand(time(NULL));
	if (!(ants = (t_ant **)malloc(sizeof(t_ant *) * map->count + 100)))
		exit(1);
	while (i < map->count)
	{
		if (!(ants[i] = (t_ant *)malloc(sizeof(t_ant) + 100)))
			exit(1);
		ants[i]->visu_x =
		map->arr_cell[map->start]->cell->x * 46 + v->padding_x + 9;
		ants[i]->visu_y =
		map->arr_cell[map->start]->cell->y * 46 + v->padding_y + 9;
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

void	draw_rooms_comp(t_edge *edges, t_map *map, t_vis *v, t_pair **tmp)
{
	*tmp = v->solmove->pairlst;
	edges = map->edges;
	change_color(255, 255, 255, v);
	draw_edges(edges, v->padding_x, v->padding_y, v);
	change_color(40, 180, 180, v);
	draw_rooms(map, v, v->padding_x, v->padding_y);
}

void	print_rooms(t_map *map, t_vis *v)
{
	t_edge			*edges;
	t_pair			*tmp;
	t_printrooms	*p;

	edges = NULL;
	init_printrooms(&p);
	draw_rooms_comp(edges, map, v, &tmp);
	while (tmp)
	{
		if (visumove_ant(v, map, tmp->ant_i - 1, tmp->room_name))
			tmp->isdone = 1;
		if (tmp->isdone)
			p->countdone++;
		p->countpair++;
		tmp = tmp->next;
	}
	if (p->countpair == p->countdone && v->solmove->next)
		v->solmove = v->solmove->next;
	while (p->i < map->count)
	{
		change_color(v->ants[p->i]->color[0],
		v->ants[p->i]->color[1], v->ants[p->i]->color[2], v);
		draw_square(v->ants[p->i]->visu_x, v->ants[p->i]->visu_y, 18, v);
		p->i++;
	}
}
