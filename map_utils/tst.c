

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
    // printf("-----------------------\n");
    while(map[++y])
    {
        x=-1;
        while(map[y][++x])
        {
            // printf("%c\n",map[y][x]);
            if(map[y][x]!='1' &&  map[y][x]!=' ')
            {
                if(y==0 || map[y-1][x] == ' ')
                {
                    printf("Error5\n");
                    exit(0);
                }
                if(x==0 || map[y][x-1] == ' ')
                {
                    printf("Error7\n");
                    exit(0);
                }
                if(y+1>data->y_map_size || map[y+1][x] == ' ')
                {
                    printf("Error4 ((%c))\n", map[y+1][x]);
                    exit(0);
                }
                if(x+1>data->x_map_size || map[y][x+1] == ' ')
                {
                    printf("Error0\n");
                    exit(0);
                }
            }
        }
        // printf("-\n");
    }
    // y=-1;
    // while(map[++y])
    //     free(map[y]);
    // free(map);
    return 0;
}

int **fillmap(char **map,t_map_info *data)
{
    int **g_map;
    g_map =malloc(sizeof(int *) * data->y_map_size);
    // printf("this %d\n,",data->y_map_size);
    int i=0;
    int j=0;
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
                // printf("player in %c \n",map[i][j]);
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
                printf("error\n");
                exit (0);
            }
            j++;
        }
        free(map[i]);
        i++;
    }
    free(map);
    return g_map;

}
void	fill_texture_info(char **wow,t_map_info *data);
int cool(char **av,t_map_info *data)
{
    int shouldstop=0;
    int fd = open(av[1], O_RDONLY);
    char *g;
    char    *trimed_str;
    int large=0;
    int len;
	g = get_next_line(fd);
    len = ft_strlen(g);
    int ylen=0;
    int j;
    char *str_for_data=ft_strdup("");
    int i=0;
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
    // pause();
    char *str=ft_strdup("");
    // g=0;
	g = get_next_line(fd);
    while (g)
	{
         trimed_str = ft_strtrim(g,"\n ");
        int nb=ft_strlen(trimed_str);
        free(trimed_str);
        // printf("%d\n",nb);
        if(nb>2)
            break;
		free(g);
		g = get_next_line(fd);
	}

    while (g)
	{
        len = ft_strlen(g);
        if(g[len-1]=='\n')
            len--;
        if(shouldstop || !len)
        {
            printf("error\n");
            exit(0);
        }
        if(len<2 )
            shouldstop=1;
        large = MAX(len,large);
        str=ft_strjoin_gnl(str,g);
		free(g);
		g = get_next_line(fd);
        ylen++;
	}

    char **map;
    char **splited = ft_split(str,'\n');
    free(str);
    map=malloc(sizeof(char *) * (ylen+1));
    data->y_map_size=ylen;
    data->x_map_size=large;
    for(i =0; splited[i] ; i++)
    {
        map[i]=malloc(large+1);
        j=0;
        while(splited[i][j])
        {
            map[i][j]=splited[i][j];
            j++;
        }
        free(splited[i]);
        while(j<large)
        {
            map[i][j]=' ';
            j++;
        }
        map[i][j]=0;
    }
    free(splited);
    map[i]=0;
    check_walls(map,data);
    data->number_of_sprites=0;
    data->map = fillmap(map,data);

    return 0;
}