/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rooms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:49:56 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/12 19:03:17 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

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