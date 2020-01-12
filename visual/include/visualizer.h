/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 20:27:58 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/12 19:03:21 by oelaina          ###   ########.fr       */
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

void		change_color(int r, int g, int b, t_vis *v);
void			parser(t_map *map);
void		draw_rectangle(int start_x, int start_y, t_vis *v);
void		draw_square(int start_x, int start_y, int size, t_vis *v);
void		draw_background(t_vis *v);
void		drawline(int x0, int y0, int x1, int y1, t_vis *v);
void    	print_rooms(t_map *map, t_vis *v);


#endif
