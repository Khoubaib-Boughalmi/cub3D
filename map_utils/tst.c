

#include "get_next_line.h"
#include "../libft/libft.h"
#include <stdio.h>
#include "../inc/cub3d.h"
#include <math.h>

// #define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))


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
                {
                    free_split(map);
                    printf("Error\n");
                    exit(0);
                }
                if(x==0 || map[y][x-1] == ' ')
                {
                    free_split(map);
                    printf("Error\n");
                    exit(0);
                }
                if(y+1>data->y_map_size || map[y+1][x] == ' ')
                {
                    free_split(map);
                    printf("Error\n");
                    exit(0);
                }
                if(x+1>data->x_map_size || map[y][x+1] == ' ')
                {
                    free_split(map);
                    printf("Error\n");
                    exit(0);
                }
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


int **fillmap(char **map,t_map_info *data)
{
    int i=0;
    int j=0;
    int player_mara=0;
    int **g_map;
    g_map =malloc(sizeof(int *) * data->y_map_size);
    while(map[i])
    {
        g_map[i]=malloc(sizeof(int) * data->x_map_size);
        j=0;
        while(j<data->x_map_size)
        {
            if(map[i][j]=='1')
                g_map[i][j]=1;
            else if(map[i][j]==' ')
                g_map[i][j]=-1;
            else if(map[i][j]=='d')
                g_map[i][j]=500;
            else if(map[i][j]=='N' ||map[i][j]=='S'||map[i][j]=='W'||map[i][j]=='E')
            {
                if(player_mara==1)
                {
                    free_g_map(g_map,i+1);
                    free_split(map);
                    printf("Error player number  \n");
                    exit (0);
                }
                g_map[i][j]=0;
                if(map[i][j]=='N' )
                    data->angle_player= 270;
                if(map[i][j]=='S' )
                    data->angle_player= 90;
                if(map[i][j]=='W' )
                    data->angle_player= 180;
                if(map[i][j]=='E' )
                    data->angle_player= 0;
                data->x_player=j*64;
                data->y_player=i*64;
                player_mara++;
            }
            else if (map[i][j]=='0')
            {
                g_map[i][j]=0;
            }
            else if (map[i][j]=='#')
            {
                if(data->number_of_sprites <15)
                    data->number_of_sprites++;
                g_map[i][j]=-2;
            }
            else
            {
                free_g_map(g_map,i+1);
                free_split(map);
                printf("error\n");
                exit (0);
            }
            j++;
        }
        i++;
    }
    if(player_mara==0)
    {
        free_g_map(g_map,i+1);
        free_split(map);
        printf("Error player number \n");
        exit (0);
    }
    free_split(map);
    return g_map;

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
        data->x_map_size = MAX(len,data->x_map_size);
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
    data->map = fillmap(map,data);
    return 0;
}
