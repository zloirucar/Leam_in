/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_move_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 12:34:55 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/17 19:00:24 by skrabby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visualizer.h"

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
