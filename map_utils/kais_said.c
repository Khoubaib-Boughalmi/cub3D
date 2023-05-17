/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kais_said.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:28:05 by kboughal          #+#    #+#             */
/*   Updated: 2023/05/17 21:43:04 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	check_num_line(char **wow)
{
	int		i;
	int		count_lines;
	char	**split_line;

	i = 0;
	count_lines = 0;
	while (wow[i])
	{
		split_line = ft_split(wow[i], ' ');
		if (split_arr_len(split_line) > 1)
			count_lines++;
		free_split(split_line);
		i++;
	}
	if (count_lines != 6)
	{
		printf("ERROR MAP DATA\n");
		free_split(wow);
		exit (1);
	}
}

void	assign_texture_values(char **split_line, t_map_info *data)
{
	if (!ft_strncmp(split_line[0], "NO", ft_strlen(split_line[0])))
		data->NO_texure = ft_strdup(split_line[1]);
	if (!ft_strncmp(split_line[0], "SO", ft_strlen(split_line[0])))
		data->SO_texure = ft_strdup(split_line[1]);
	if (!ft_strncmp(split_line[0], "EA", ft_strlen(split_line[0])))
		data->EA_texure = ft_strdup(split_line[1]);
	if (!ft_strncmp(split_line[0], "WE", ft_strlen(split_line[0])))
		data->WE_texure = ft_strdup(split_line[1]);
}

void	fill_texture_info_core_norm(char **wow, char **options_check, \
		char **options_list, char **split_line)
{
	static int	k = 0;

	if (find_in_list(options_list, split_line[0]))
		options_check[k++] = ft_strdup(split_line[0]);
	else
		free_and_exit(split_line, options_check, options_list, wow);
}

void	fill_texture_info_core(char **wow, char **ol, \
		char **oc, t_map_info *data)
{
	int		i;
	int		k;
	char	**split_line;

	i = 0;
	k = 0;
	while (wow[i])
	{
		wow[i] = ft_trim_str(wow[i]);
		if (ft_strlen(wow[i]))
		{
			split_line = ft_split(wow[i], ' ');
			if (split_arr_len(split_line) == 2)
			{
				fill_texture_info_core_norm(wow, oc, ol, split_line);
				if (!check_floor_ceiling(split_line, data))
					free_and_exit(split_line, oc, ol, wow);
			}
			else
				free_and_exit(split_line, oc, ol, wow);
			assign_texture_values(split_line, data);
			free_split(split_line);
		}
		i++;
	}
}

void	fill_texture_info(char **wow, t_map_info *data)
{
	int		i;
	char	*options;
	char	**options_list;
	char	**options_check;

	i = 0;
	options = "NO SO WE EA F C";
	check_num_line(wow);
	options_check = (char **)malloc(sizeof(char *) * 7);
	if (!options_check)
		exit(1);
	options_check[6] = NULL;
	options_list = ft_split(options, ' ');
	fill_texture_info_core(wow, options_list, options_check, data);
	free_split(wow);
	textures_naming_err(options_check, options_list);
	free_split(options_list);
	free_split(options_check);
}
