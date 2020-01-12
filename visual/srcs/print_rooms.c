/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:49:56 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/12 19:57:11 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static  int    set_param(t_edge **edges, int padding_x, int padding_y, t_vis *v)
{
    int x1;
    int x2;
    int y1;
    int y2;
    int i;

    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;
    i  = 0;
    if ((*edges)->first_node->x * 46 + padding_x <
        (*edges)->second_node->x * 46 + padding_x)
        {
            x1 = (*edges)->first_node->x * 46 + padding_x + 18;
            x2 = (*edges)->second_node->x * 46 + padding_x + 18;
            y1 = (*edges)->first_node->y * 46 + padding_y + 18;
            y2 = (*edges)->second_node->y * 46 + padding_y + 18;
            i = 1;
        }
    else
         return (i);
    drawline(x1, y1, x2, y2, v);
    (*edges) = (*edges)->next;
    return (i);
}

static  void    set_another_param(t_edge **edges, int padding_x, int padding_y, t_vis *v)
{
    int x1;
    int x2;
    int y1;
    int y2;

    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;
    x2 = (*edges)->first_node->x * 46 + padding_x + 18;
    x1 = (*edges)->second_node->x * 46 + padding_x + 18;
    y2 = (*edges)->first_node->y * 46 + padding_y + 18;
    y1 = (*edges)->second_node->y * 46 + padding_y + 18;
    drawline(x1, y1, x2, y2, v);
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
            change_color(0, 0, 0, v);
            draw_square(coordx, coordy, 36, v);
            change_color(255, 100, 255, v);
            count++;
            continue;
        }
        if(count == map->end)
        {
            change_color(255, 255, 255, v);
            draw_square(coordx, coordy, 36, v);
            change_color(255, 100, 255, v);
            count++;
            continue;
        }
        draw_square(coordx, coordy, 36, v);
        count++;
    }
}

void    print_rooms(t_map *map, t_vis *v)
{
    int padding_x;
    int padding_y;
    t_edge *edges;

    padding_x = 300;
    padding_y = 75;
    edges = map->edges;
    change_color(255, 255, 255, v);
    // edges
    draw_edges(edges, padding_x, padding_y, v);
    change_color(255, 100, 255, v);
    //rooms
    draw_rooms(map, v, padding_x, padding_y);
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