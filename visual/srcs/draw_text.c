/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 13:52:33 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/18 18:38:14 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

void	draw_ant_index(t_vis *v)
{
	int i;
	char *tmp;

	i = 0;
	while (i < v->map->count)
	{
		tmp = ft_itoa(v->ants[i]->index);
		if (i < v->map->count - v->start_room_ants &&
			(v->ants[i]->visu_x !=
			v->map->arr_cell[v->map->end]->cell->x * 46 + v->padding_x + 9
			|| v->ants[i]->visu_y !=
			v->map->arr_cell[v->map->end]->cell->y * 46 + v->padding_y + 9))
			mlx_string_put(v->mlx, v->win, v->ants[i]->visu_x + 18,
			v->ants[i]->visu_y + 18, 0x0FFFFFF, tmp);
		i++;
		free(tmp);
	}
}

void	draw_room_name(t_vis *v)
{
	int		coordx;
	int		coordy;
	t_cell	*tmp;

	tmp = v->map->cells;
	while (tmp)
	{
		coordx = tmp->x * 46 + v->padding_x;
		coordy = tmp->y * 46 + v->padding_y - 5;
		mlx_string_put(v->mlx, v->win, coordx,
		coordy, 0x0FFFFFF, tmp->name);
		tmp = tmp->next;
	}
}

void	draw_end_start(t_vis *v)
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
