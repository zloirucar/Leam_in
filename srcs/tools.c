/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelaina <oelaina@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 11:08:20 by oelaina           #+#    #+#             */
/*   Updated: 2020/01/18 21:57:10 by oelaina          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	ft_printpair(int d, char *s)
{
	ft_putchar('L');
	ft_putnbr(d);
	ft_putchar('-');
	ft_putstr(s);
}

void	clear_2d_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr[i]);
	free(arr);
}

int		check_char(char *line, char c)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	error_msg(void)
{
	ft_fprintf(1, "ERROR\n");
	exit(1);
}

void	check_valid(char **loc_line, char *line)
{
	ft_printf("%s\n", line);
	while (get_next_line(0, loc_line))
	{
		if (*loc_line[0] == '#')
		{
			free(*loc_line);
			continue ;
		}
		if (*loc_line[0] == 'L')
			error_msg();
		else
			break ;
	}
}
