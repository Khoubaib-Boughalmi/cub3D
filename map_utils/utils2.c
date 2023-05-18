/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 20:09:17 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/18 14:53:15 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	assign_rgb_colors(t_map_info *data, char *str, int selecter, char val)
{
	if (val == 'F')
	{
		if (selecter == 0)
			data->f_color.r = ft_atoi(str);
		if (selecter == 1)
			data->f_color.g = ft_atoi(str);
		if (selecter == 2)
			data->f_color.b = ft_atoi(str);
	}
	else
	{
		if (selecter == 0)
			data->c_color.r = ft_atoi(str);
		if (selecter == 1)
			data->c_color.g = ft_atoi(str);
		if (selecter == 2)
			data->c_color.b = ft_atoi(str);
	}
}

int	is_numerical(t_map_info *data, char *str, int selecter, char val)
{
	int	i;

	i = 0;
	if (ft_strlen(str) > 3)
		return (0);
	while (str[i] && str[i] != '\n')
	{
		if (!ft_isnumber(str[i]))
			return (0);
		i++;
	}
	if (ft_atoi(str) > 255)
		return (0);
	assign_rgb_colors(data, str, selecter, val);
	return (1);
}

int	check_floor_ceiling_core(t_map_info *data, \
	char **ceiling_floor_lst, char *name, char *value)
{
	int	i;

	i = 0;
	while (ceiling_floor_lst[i])
	{
		if (!ft_strncmp(name, "F", ft_strlen(value)))
		{
			if (!is_numerical(data, ceiling_floor_lst[i], i, 'F'))
			{
				free_split(ceiling_floor_lst);
				return (0);
			}
		}
		else
		{
			if (!is_numerical(data, ceiling_floor_lst[i], i, 'C'))
			{
				free_split(ceiling_floor_lst);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	check_floor_ceiling(char **floor_ceiling, t_map_info *data)
{
	char	**ceiling_floor_lst;
	char	*name;
	char	*value;
	int		i;

	i = 0;
	name = floor_ceiling[0];
	value = floor_ceiling[1];
	if (!ft_strncmp(name, "F", ft_strlen(value)) || \
		!ft_strncmp(name, "C", ft_strlen(value)))
	{
		ceiling_floor_lst = ft_split(value, ',');
		if (split_arr_len(ceiling_floor_lst) != 3)
			return (0);
		if (!check_floor_ceiling_core(data, ceiling_floor_lst, name, value))
			return (0);
		free_split(ceiling_floor_lst);
	}
	return (1);
}

char	*ft_trim_str(char *str)
{
	int		i;
	int		j;
	int		k;
	char	*new_str;

	i = 0;
	k = 0;
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (str[i] && (str[i] == ' ' || str[i] == '\n'))
		i++;
	j = ft_strlen(str) - 1;
	while (j > 0 && (str[j] == ' ' || str[j] == '\n'))
		j--;
	while (str[i] && i <= j)
	{
		new_str[k] = str[i];
		i++;
		k++;
	}
	new_str[k] = '\0';
	free(str);
	return (new_str);
}
