/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cell.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 20:13:48 by oelaina           #+#    #+#             */
/*   Updated: 2019/12/08 21:15:59 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	set_cell(t_cell *cell, char *line)
{
	char	**arr;
	int		i;

	i = 0;
	arr = ft_strsplit(line, ' ');
	cell->name = ft_strdup(arr[0]);
	cell->y = ft_atoi(arr[1]);
	cell->x = ft_atoi(arr[2]);
	while (arr[i] != '\0')
	{
		free(arr[i]);
		i++;
	}
	free (arr[i]);
	free(arr);
}

t_cell	*init_cell()
{
	t_cell	*cell;

	if(!(cell = (t_cell *)malloc(sizeof(t_cell))))
		exit(1);
	cell->size_neib = 0;
	return (cell);
}

void	arr_cellcpy(t_cell **dest, t_cell **src, int size)
{
	int flag;

	flag = size;
	while (size >= 0)
	{
		dest[size] = init_cell();
		dest[size]->name = src[size]->name;
		dest[size]->y = src[size]->y;
		dest[size]->x = src[size]->x;
		free (src[size]);
		size--;
	}
}

void	inc_arr_cell(t_cell ***arr_cell, int* size)
{
	t_cell	**buff;

	if (!(buff = (t_cell **)malloc(sizeof(t_cell *) * (*size))))
		exit (1);
	arr_cellcpy(buff, *arr_cell, *size - 1);
	if (*size - 1 <= 0)
		free (*arr_cell);
	if(!(*arr_cell = (t_cell **)malloc(sizeof(t_cell *) * (*size + 1))))
		exit (1);
	arr_cellcpy(*arr_cell, buff, *size - 1);
	if (*size - 1 <= 0)
		free (buff);
	(*size)++;
}
