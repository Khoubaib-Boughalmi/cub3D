/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lol_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aechaoub <aechaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:56:35 by aechaoub          #+#    #+#             */
/*   Updated: 2023/04/26 21:48:07 by aechaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	addsecend_toarr_1_k(t_data *mapty, t_val *val)
{
	mapty->map.map[val->j][val->i] = 3;
	mapty->enemy.many++;
	mapty->enemy.xplace = val->i;
	mapty->enemy.yplace = val->j;
}

void	addsecend_toarr_1_p(t_data *mapty, t_val *val)
{
	mapty->map.map[val->j][val->i] = 7;
	mapty->gras.many++;
	mapty->map.xstart = val->i;
	mapty->map.ystart = val->j;
	mapty->small.x = mapty->map.xstart * 50;
	mapty->small.y = mapty->map.ystart * 50;
	mapty->small.xplace = mapty->map.xstart;
	mapty->small.yplace = mapty->map.ystart;
}

void	addsecend_toarr_1(t_data *mapty, int len, char *g, t_val *val)
{
	while (val->i < len)
	{
		if (g[val->i] == '1')
			mapty->map.map[val->j][val->i] = 1;
		else if (g[val->i] == '0')
			mapty->map.map[val->j][val->i] = 0;
		else if (g[val->i] == 'C')
		{
			mapty->dollar.many += 1;
			mapty->map.map[val->j][val->i] = 5;
		}
		else if (g[val->i] == 'E')
		{
			mapty->map.map[val->j][val->i] = 8;
			mapty->door.many++;
		}
		else if (g[val->i] == 'P')
			addsecend_toarr_1_p(mapty, val);
		else if (g[val->i] == ' ')
			mapty->map.map[val->j][val->i] = 3;			
		else if (g[val->i] != '\n')
			exitfunc(mapty);
		val->i++;
	}
}
int max(int a ,int b)
{
	if (a>b)
		return a;
	return b;
}

void	addsecend_toarr(t_data *mapty, char *av, int **map)
{
	char	*g;
	t_val	val;
	int		len;
	int		basiclen;
	int		fd;

	fd = open(av, O_RDONLY);
	g = get_next_line(fd);
	basiclen = ft_strlen(g);
	val.j = 0;
	mapty->map.x = 0;
	while (g)
	{
		len = ft_strlen(g);
		mapty->map.map[val.j] = malloc(len * 8);
		if (len != basiclen)
			mapty->map.x = max(len,mapty->map.x);
		val.i = 0;
		free(map[val.j]);
		addsecend_toarr_1(mapty, len, g, &val);
		val.j++;
		free(g);
		g = get_next_line(fd);
	}
	// mapty->map.x += val.i - 1;
	mapty->map.y = val.j;
}

void	checkext(char *av)
{
	if (ft_strncmp(av + ft_strlen(av) - 4, ".ber", 5))
	{
		ft_putstr("The map description file must end with the .ber extension\n");
		exit(0);
	}
}
