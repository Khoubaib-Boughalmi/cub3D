/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 20:08:21 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/18 14:28:35 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	split_arr_len(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

int	find_in_list(char **options_list, char *needle)
{
	int	i;

	i = 0;
	while (options_list[i])
	{
		if (!ft_strncmp(options_list[i], needle, ft_strlen(needle)))
			return (1);
		i++;
	}
	return (0);
}

int	check_all_elem(char **options_check)
{
	int	i;
	int	j;

	i = 0;
	while (options_check[i])
	{
		j = i + 1;
		while (options_check[j])
		{
			if (!(ft_strncmp(options_check[i], \
			options_check[j], ft_strlen(options_check[j]))))
				return (0);
			j++;
		}
		i++;
	}	
	return (1);
}

int	ft_isnumber(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
