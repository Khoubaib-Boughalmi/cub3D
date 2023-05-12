/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lol.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:58:45 by aechaoub          #+#    #+#             */
/*   Updated: 2023/04/26 20:42:17 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	checkmove(int **tab, int x, int y)
{
	int	i;
	int	j;

	j = 0;
	while (j < y)
	{
		i = 0;
		while (i < x)
		{
			if (tab[j][i] == 7)
			{
				if (tab[j + 1][i] == 0 || tab[j - 1][i] == 0
					|| tab[j][i + 1] == 0 || tab[j][i - 1] == 0
						||tab[j + 1][i] == 5 || tab[j - 1][i] == 5
							|| tab[j][i + 1] == 5 || tab[j][i - 1] == 5
								|| tab[j + 1][i] == 8 || tab[j - 1][i] == 8
									|| tab[j][i + 1] == 8 || tab[j][i - 1] == 8)
					return (1);
			}
			i++;
		}
		j++;
	}
	return (0);
}

void	planmap_2(int **tab, int i, int j)
{
	if (tab[j][i] == 7)
	{
		if (tab[j + 1][i] == 0 || tab[j + 1][i] == 8 || tab[j + 1][i] == 5)
			tab[j + 1][i] = 7;
		if (tab[j - 1][i] == 0 || tab[j - 1][i] == 8 || tab[j - 1][i] == 5)
			tab[j - 1][i] = 7;
		if (tab[j][i + 1] == 0 || tab[j][i + 1] == 8 || tab[j][i + 1] == 5)
			tab[j][i + 1] = 7;
		if (tab[j][i - 1] == 0 || tab[j][i - 1] == 8 || tab[j][i - 1] == 5)
			tab[j][i - 1] = 7;
	}
}

void	free_tab(int **tab, int j)
{
	int	i;

	i = 0;
	while (tab[i] && i < j)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	write(1, "error  .", 8);
	exit(0);
}

void	planmap( int **tab, int x, int y)
{
	int	i;
	int	j;

	while (checkmove(tab, x, y))
	{
		j = 0;
		while (j < y)
		{
			i = 0;
			while (i < x)
			{
				if (tab[0][i] != 1 || tab[y - 1][i] != 1
					|| tab[j][0] != 1 || tab[j][x - 1] != 1)
					free_tab(tab, j);
				planmap_2(tab, i, j);
				i++;
			}
			j++;
		}
	}
}

void	getrslt(t_data *mapty, char *av)
{
	int		**map;

	checkext(av);
	map = add_toarr(mapty, av);
	mapty->map.x = 0;
	addsecend_toarr(mapty, av, map);
	free(map);
	if (mapty->enemy.many > 1 || mapty->door.many != 1
		|| mapty->gras.many != 1)
		exitfunc(mapty);
}
#include <stdio.h>

int main(int ac , char **av)
{
		t_data	img;
	if (ac != 2)
		return (0);
	img.door.many = 0;
	img.gras.many = 0;
	img.small.many = 0;
	img.dollar.many = 0;
	getrslt(&img, av[1]);
	for(int i=0;i<img.map.y;i++)
	{
		for(int j=0;j<img.map.x;j++)
		{
			printf("%d",img.map.map[i][j]);
		}
			printf("\n");
		
	}
}