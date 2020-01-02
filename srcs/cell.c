/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 20:13:48 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/02 18:32:27 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	set_cell(t_cell *cell, char *line, int index)
{
	char	**arr;
	int		i;

	i = 0;
	arr = ft_strsplit(line, ' ');
	cell->name = ft_strdup(arr[0]);
	cell->y = ft_atoi(arr[1]);
	cell->x = ft_atoi(arr[2]);
	cell->is_visited = 0;
	cell->distance = 0;
	cell->prev = NULL;
	cell->next = NULL;
	cell->next_neib = NULL;
	cell->index = index;
	while (arr[i])
	{
//		free(arr[i]);
		i++;
	}
//	free (arr[i]);
//	free(arr);
}

t_cell	*init_cell()
{
	t_cell	*cell;

	if(!(cell = (t_cell *)malloc(sizeof(t_cell))))
		exit(1);
	return (cell);
}

void	arr_cellcpy(t_cell **dest, t_cell **src, int size)
{
	while (size >= 0)
	{
		dest[size] = init_cell();
		dest[size]->name = src[size]->name;
		dest[size]->y = src[size]->y;
		dest[size]->x = src[size]->x;
		//dest[size]->index = src[size]->index;
	//	ft_printf("ADDRESS DEST : %p, ADDRES SRC: %p\n", dest[size]->neib, src[size]->neib);
/*		while (i < dest[size]->size_neib)
		{
			ft_printf("NAME dest %s NAME SRC %s\n", dest[size]->neib[i]->name, src[size]->neib[i]->name);
			i++;
		}*/
		//free (src[size]);
		size--;
	}
}

void	inc_arr_cell(t_cell ***arr_cell, int* size)
{
	t_cell	**buff;

	if (!(buff = (t_cell **)malloc(sizeof(t_cell *) * (*size))))
		exit (1);
	arr_cellcpy(buff, *arr_cell, *size - 1);
	//if (*size - 1 >= 0)
	//	free (*arr_cell);
	if(!(*arr_cell = (t_cell **)malloc(sizeof(t_cell *) * (*size + 1))))
		exit (1);
	arr_cellcpy(*arr_cell, buff, *size - 1);
	if (*size - 1 >= 0)
		free (buff);
	(*size)++;
}