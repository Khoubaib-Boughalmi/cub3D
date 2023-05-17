

#include "get_next_line.h"
#include "../libft/libft.h"
#include <stdio.h>
#include "../inc/cub3d.h"
#include <math.h>

int ft_max(int a,int b)
{
    if(a>b)
        return a;
    return b;
}

void check_walls_exit(char **map)
{
    free_split(map);
    printf("Error\n");
    exit(0);
}

int check_walls(char **map,t_map_info *data)
{
    int x=-1;
    int y=-1;
    while(map[++y])
    {
        x=-1;
        while(map[y][++x])
        {
            if(map[y][x]!='1' &&  map[y][x]!=' ')
            {
                if(y==0 || map[y-1][x] == ' ')
                    check_walls_exit(map);
                if(x==0 || map[y][x-1] == ' ')
                    check_walls_exit(map);
               if(y+1>data->y_map_size || map[y+1][x] == ' ')
                    check_walls_exit(map);
               if(x+1>data->x_map_size || map[y][x+1] == ' ')
                    check_walls_exit(map);
           }
        }
    }
    return 0;
}

void free_g_map(int **map,int till)
{
    int i=0;
    while(i<till)
    {
        free(map[i]);
        i++;
    }
    free(map);

}
int **allocate_map_memory(int y_size, int x_size)
{
    int **map = malloc(sizeof(int *) * y_size);
    for (int i = 0; i < y_size; i++) {
        map[i] = malloc(sizeof(int) * x_size);
    }
    return map;
}
void fillmap_exit(char **map,t_map_info *data)
{
    free_g_map(data->map,data->y_map_size);
    free_split(map);
    printf("Error  number of content \n");
    exit (0);
}


void set_player_info(char cell, t_map_info *data, int i, int j)
{
    if (cell == 'N')
        data->angle_player = 270;
    else if (cell == 'S')
        data->angle_player = 90;
    else if (cell == 'W')
        data->angle_player = 180;
    else if (cell == 'E')
        data->angle_player = 0;

    data->x_player = j * 64;
    data->y_player = i * 64;
}


void set_map_value(char **map,t_map_info *data,int **g_map,int i,int j)
{
    if(map[i][j]=='1')
        g_map[i][j]=1;
    else if(map[i][j]==' ')
        g_map[i][j]=-1;
    else if(map[i][j]=='d')
        g_map[i][j]=500;
    else if (map[i][j]=='0')
        g_map[i][j]=0;
    else if (map[i][j]=='#')
    {
        if(data->number_of_sprites <15)
            data->number_of_sprites++;
        g_map[i][j]=-2;
    }
    else
        fillmap_exit(map,data);
}

void fillmap(char **map,t_map_info *data)
{
    int i=0;
    int j=0;
    int player_mara=0;
    data->map =allocate_map_memory(data->y_map_size, data->x_map_size);
    while(map[i])
    {
        j=0;
        while(j<data->x_map_size)
        {
            if(map[i][j]=='N' ||map[i][j]=='S'||map[i][j]=='W'||map[i][j]=='E')
            {
                if(player_mara==1)
                    fillmap_exit(map,data);
                data->map[i][j]=0;
                set_player_info(map[i][j], data, i, j);
                player_mara++;
            }
            else
                set_map_value(map,data,data->map,i,j);
            j++;
        }
        i++;
    }
    if(player_mara==0)
        fillmap_exit(map,data);
    free_split(map);

}
void	fill_texture_info(char **wow,t_map_info *data);



void get_data_to_fill_texture_info(int fd,t_map_info *data)
{
    char    *trimed_str;
    int i=0;
    char *str_for_data=ft_strdup("");
	char *g = get_next_line(fd);
    while (g)
	{
        trimed_str = ft_strtrim(g,"\n ");
        int nb=ft_strlen(trimed_str);
        free(trimed_str);
        if(nb>2)
            i++;
        str_for_data=ft_strjoin_gnl(str_for_data,g);
		free(g);
        if(i==6)
            break;
		g = get_next_line(fd);
	}
    char **dbl =ft_split(str_for_data,'\n');
    free(str_for_data);
    fill_texture_info(dbl,data);
}


char *skip_all_lines_before_the_map(int fd)
{
    char    *trimed_str;
    char *g = get_next_line(fd);
    while (g)
	{
        trimed_str = ft_strtrim(g,"\n ");
        int nb=ft_strlen(trimed_str);
        free(trimed_str);
        if(nb>2)
            break;
		free(g);
		g = get_next_line(fd);
	}
    return g;
}

char **get_the_map_from_file(char *g,int fd,t_map_info *data)
{
    int shouldstop=0;
    int len;
    char *str=ft_strdup("");
    while (g)
	{
        len = ft_strlen(g);
        if(g[len-1]=='\n')
            len--;
        if(shouldstop || !len)
        {
            printf("error\n");
            free(g);
            free(str);
            exit(1);
        }
        if(len<2 )
            shouldstop=1;
        data->x_map_size = ft_max(len,data->x_map_size);
        str=ft_strjoin_gnl(str,g);
		free(g);
		g = get_next_line(fd);
        data->y_map_size++;
	}
    char **splited = ft_split(str,'\n');
    free(str);
    return splited;
}


char **get_the_map_from_last_funct(t_map_info *data,char **splited)
{
    char **map;
    int i=-1;
    int j;
    map=malloc(sizeof(char *) * (data->y_map_size+1));
    while(splited[++i])
    {
        map[i]=malloc(data->x_map_size+1);
        j=-1;
        while(splited[i][++j])
            map[i][j]=splited[i][j];
        free(splited[i]);
        while(j<data->x_map_size)
        {
            map[i][j]=' ';
            j++;
        }
        map[i][j]=0;
    }
    map[i]=0;
    free(splited);
    return map;
}



int cool(char **av,t_map_info *data)
{
    int fd = open(av[1], O_RDONLY);
    char *g;
    data->y_map_size=0;
    data->x_map_size=0;
    get_data_to_fill_texture_info(fd,data);
    g= skip_all_lines_before_the_map(fd);
    char **splited = get_the_map_from_file(g,fd,data);
    char **map = get_the_map_from_last_funct(data,splited);
    check_walls(map,data);
    data->number_of_sprites=0;
    fillmap(map,data);
    return 0;
}
