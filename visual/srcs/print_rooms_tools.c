/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rooms_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 12:40:33 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/17 12:49:30 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

static	int		set_param(t_edge **edges,
					int padding_x, int padding_y, t_vis *v)
{
	int		i;
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

static	void	set_another_param(t_edge **edges,
					int padding_x, int padding_y, t_vis *v)
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

void			draw_edges(t_edge *edges,
					int padding_x, int padding_y, t_vis *v)
{
	while (edges)
	{
		if (set_param(&edges, padding_x, padding_y, v) == 0)
			set_another_param(&edges, padding_x, padding_y, v);
	}
}
