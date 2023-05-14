#include "get_next_line.h"
#include "../libft/libft.h"
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

int	is_numerical(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if(!ft_isnumber(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	check_floor_ceiling(char **floor_ceiling)
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
		while (ceiling_floor_lst[i])
		{
			if(!is_numerical(ceiling_floor_lst[i]))
				return (0);
			i++;
		}
	}
	return (1);
}

void	fill_texture_info()
{
	int32_t c_color;
	int32_t f_color;
	char *NO_texure;
	char *SO_texure;
	char *WE_texure;
	char *EA_texure;
	int	count = 0;
	int	count_lines = 0;
	char	*line;
	char **split_line;
	char	*options = "NO SO WE EA F C"; 
	char	**options_list;
	char	**options_check;
	int	k;
	int	err;

	k = 0;
	err = 0;
	int fd = open("../map.ber", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		split_line = ft_split(line, ' ');
		if(split_arr_len(split_line) > 1)
			count_lines++;
		free(line);
		free_split(split_line);
		line = get_next_line(fd);
	}
	if(count_lines != 6)
	{
		printf("ERROR MAP DATA\n");
		return ;
	}
	options_check = (char **)malloc(sizeof(char *) * 7);
	options_check[6] = NULL;
	options_list = ft_split(options, ' ');
	close(fd);
	fd = open("../map.ber", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		split_line = ft_split(line, ' ');
		if(split_arr_len(split_line) > 1)
		{
			if(find_in_list(options_list, split_line[0]))
				options_check[k++] = ft_strdup(split_line[0]);
			else
			{
				printf("Wrong texture DATA\n");
				err++;
			}
			if(!check_floor_ceiling(split_line))
			{
				printf("ERROR with floor/ceiling data\n");		
				err++;
			}
		}
		free(line);
		free_split(split_line);
		line = get_next_line(fd);
	}
	if(!err && !check_all_elem(options_check))	
		printf("ERROR with textures data");
	free_split(options_list);
	free_split(options_check);
}

int main()
{
	fill_texture_info();
	return (0);
}