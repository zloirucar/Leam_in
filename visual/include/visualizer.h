/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 20:27:58 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/16 13:35:47 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H
# define HEIGHT 900
# define WIDTH 1450
# define ESC 53
# define SPACE 49
# define WINDOW_NAME "Lem-in Visualizer"

# include "mlx.h"
# include "lem_in.h"

typedef struct			s_ant
{
	int					index; // ant's index
	int					visu_x; // x coordinate on visualizer
	int					visu_y; // y coordinate on visualizer
	float				carry_x;
	float				carry_y; // for smooth visu
	int					color[3]; // rgb color of ant;					
}						t_ant;

typedef struct			s_pair
{
	int					ant_i;
	char				*room_name;
	int					isdone;
	struct s_pair		*next;
}						t_pair;

typedef struct			s_solmove
{
	t_pair				*pairlst;
	struct s_solmove	*next;
}						t_solmove;

typedef struct			s_vis
{
	int					height;
	int					width;
	void				*mlx;
	void				*win;
	void				*img;
	char				*ret;
	int					endian;
	int					size_line;
	int					bits_per_pixel;
	int					red;
	int					green;
	int					blue;
	int					padding_x;
	int					padding_y;
	int					len;
	int					h;
	int					map_created;
	int					first_parse;
    t_map           	*map;
	t_ant				**ants;
	t_solmove			*solmove;
	int					start_room_ants;
	int					end_room_ants;
	int					visu_speed;
	int					trim_x0;
	int					trim_x1;
	int					trim_y0;
	int					trim_y1;
	int					pause;
}						t_vis;

typedef	struct			s_draw
{
	int					x1;
	int					y1;
	int					x2;
	int					y2;
	t_vis				*vis;	
}						t_draw;

typedef struct			s_antmove
{
	int					x0;
	int					x1;
	int					y0;
	int					y1;
	int					diffx;
	int					diffy;
	int					sign_x;
	int					sign_y;
	int					room_index;
	float				add_x;
	float				add_y;
}						t_antmove;

typedef	struct			s_drawline
{
	float 				fx0;
    float 				y_begin;
    float 				y_target;
    float 				add_x;
    float 				add_y;
    float 				y_diff;
    int					y_sign;
}						t_drawline;


void					change_color(int r, int g, int b, t_vis *v);
void					init_draw(t_draw **draw, t_vis *vis);
void					parser(t_map *map);
void					draw_rectangle(int start_x, int start_y, t_vis *v);
void					draw_square(int start_x, int start_y, int size, t_vis *v);
void					draw_background(t_vis *v);
void					drawline(t_draw *draw);
void    				print_rooms(t_map *map, t_vis *v);
void 					draw_edges(t_edge *edges, int padding_x, int padding_y, t_vis *v);
void					parse_L(void);
t_ant					**create_ants(t_map *map, t_vis *v);
t_solution				*solution_addlast(t_solution *list, char *new_str);
void					parse_solution(t_map *map, char *line);
t_solution				*init_solution(void);
void					check_error(void);
#endif
