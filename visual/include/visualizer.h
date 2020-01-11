/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skrabby <skrabby@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 20:27:58 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/11 21:42:56 by skrabby          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H
# define HEIGHT 1290
# define WIDTH 1740
# define WINDOW_NAME "Lem-in Visualizer"

# include "mlx.h"
# include "lem_in.h"

typedef struct		s_vis
{
	int				height;
	int				width;
	void			*mlx;
	void			*win;
	void			*img;
	char			*ret;
	int				endian;
	int				size_line;
	int				bits_per_pixel;
	int				red;
	int				green;
	int				blue;
	int				len;
	int				h;
	int				map_created;
	int				first_parse;
    t_map           *map;
}					t_vis;

typedef struct		s_drawmap
{
	int				y;
	int				x;
	int				tmpx;
	int				tmpy;
	int				sqlen;
	int				gap;
	int				padding_x;
	int				padding_y;
}					t_drawmap;

void			parser(t_map *map);
#endif
