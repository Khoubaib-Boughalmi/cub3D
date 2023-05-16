#include "get_next_line.h"
#include "../libft/libft.h"
#include "../inc/cub3d.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	free_split(char **arr)
{
	int	i;

	i = 0;
	if(!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);	
}

int	split_arr_len(char **arr)
{
	int	i;

	i = 0;
	if(!arr)
		return 0;
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
		if(!ft_strncmp(options_list[i], needle, ft_strlen(needle)))
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
			if(!(ft_strncmp(options_check[i], options_check[j], ft_strlen(options_check[j]))))
				return (0);
			j++;
		}
		i++;
	}	
	return (1);
}

int	ft_isnumber(char c)
{
	if(c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_numerical(t_map_info *data, char *str, int selecter, char val)
{
	int	i;

	i = 0;
	if(ft_strlen(str) > 3)
		return (0);
	while (str[i] && str[i] != '\n')
	{
		if(!ft_isnumber(str[i]))
			return (0);
		i++;
	}
	if(ft_atoi(str) > 255)
		return (0);
	if(val == 'F')
	{
		if(selecter == 0)
			data->f_color.r = ft_atoi(str);
		if(selecter == 1)
			data->f_color.g = ft_atoi(str);
		if(selecter == 2)
			data->f_color.b = ft_atoi(str);
	}
	else
	{
		if(selecter == 0)
		{
			printf("color %s\n", str);
			data->c_color.r = ft_atoi(str);
		}
		if(selecter == 1)
			data->c_color.g = ft_atoi(str);
		if(selecter == 2)
			data->c_color.b = ft_atoi(str);
	}
	return (1);
}

int	check_floor_ceiling(char **floor_ceiling, t_map_info *data)
{
	char	**ceiling_floor_lst;
	char	*name;
	char	*value;
	int	i;

	i = 0;
	name = floor_ceiling[0];
	value = floor_ceiling[1];
	if(!ft_strncmp(name, "F", ft_strlen(value)) || !ft_strncmp(name, "C", ft_strlen(value)))
	{
		ceiling_floor_lst = ft_split(value, ',');
		if(split_arr_len(ceiling_floor_lst) != 3)
			return (0);
		while (ceiling_floor_lst[i])
		{
			if(!ft_strncmp(name, "F", ft_strlen(value)))
			{
				if(!is_numerical(data, ceiling_floor_lst[i], i, 'F'))
				{
					free_split(ceiling_floor_lst);
					return (0);
				}
			}
			else
				if(!is_numerical(data, ceiling_floor_lst[i], i, 'C'))
				{
					free_split(ceiling_floor_lst);
					return (0);
				}
			i++;
		}
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
	while (j > 0  && (str[j] == ' ' || str[j] == '\n'))
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
void	fill_texture_info(char **wow,t_map_info *data)
{
	int		k;
	int		err;
	int		count_lines = 0;
	char	**split_line;
	char	*options = "NO SO WE EA F C"; 
	char	**options_list;
	char	**options_check;
    // t_map_info data;

	k = 0;
	err = 0;
	// int fd = open("parsing_map.txt", O_RDONLY);
	// line = get_next_line(fd);
	int i=0;
	while (wow[i])
	{
		// printf("%s\n",wow[i]);
		split_line = ft_split(wow[i], ' ');
		if(split_arr_len(split_line) > 1)
			count_lines++;
		// free(wow[i]);
		free_split(split_line);
		i++;
	}
	if(count_lines != 6)
	{
		printf("ERROR MAP DATA\n");
		exit(1) ;
	}
	options_check = (char **)malloc(sizeof(char *) * 7);
	options_check[6] = NULL;
	options_list = ft_split(options, ' ');
	i=0;
	while (wow[i])
	{
		wow[i] = ft_trim_str(wow[i]);
		if(ft_strlen(wow[i]))
		{
			split_line = ft_split(wow[i], ' ');
			if(split_arr_len(split_line) == 2)
			{
				if(find_in_list(options_list, split_line[0]))
					options_check[k++] = ft_strdup(split_line[0]);
				else
				{
					printf("Wrong texture DATA\n");
					free(split_line);
					free(options_check);
					free(options_list);
					free(wow);
					exit(1) ;
				}
				if(!check_floor_ceiling(split_line, data))
				{
					printf("ERROR with floor/ceiling data\n");		
					free(split_line);
					free(options_check);
					free(options_list);
					free(wow);
					exit(1);
				}
			}
			else
			{
				printf("DATA MISSING\n");
				exit(1);
			}
			if(!ft_strncmp(split_line[0], "NO", ft_strlen(split_line[0])))
				data->NO_texure = ft_strdup(split_line[1]);
			if(!ft_strncmp(split_line[0], "SO", ft_strlen(split_line[0])))
				data->SO_texure = ft_strdup(split_line[1]);
			if(!ft_strncmp(split_line[0], "EA", ft_strlen(split_line[0])))
				data->EA_texure = ft_strdup(split_line[1]);
			if(!ft_strncmp(split_line[0], "WE", ft_strlen(split_line[0])))
				data->WE_texure = ft_strdup(split_line[1]);
			free(wow[i]);
			free_split(split_line);
		}
		i++;
	}
	if(!err && !check_all_elem(options_check))	
		printf("ERROR with textures data");
	free_split(options_list);
	free_split(options_check);
	// while (1)
	// {
	// 	/* code */
	// }
	
}

// int main()
// {

//     char **str =ft_split("NO ./path_to_the_south_texture\nSO      ./path_to_the_south_texture\nWE ./path_to_the_west_texture\n\n\n\n\n\n     EA       ./path_to_the_east_texture\n\nF 220,100,0\nC 225,3,0\n",'\n');
// 	// int fd = open("parsing_map.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	// write(fd, str, ft_strlen(str));
//     fill_texture_info(str);
// 	// close(fd);
// 	// free(str);
//     return (0);
// }