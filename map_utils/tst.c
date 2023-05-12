

#include "get_next_line.h"
#include <stdio.h>
#include <math.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))



typedef struct s_map_info {
    int **map;
    double x_player;
    double y_player;
    double angle_player;
    int x_map_size;
    int y_map_size;
}				t_map_info;


// int data->x_map_size;
// int data->y_map_size;



char first_th(char *str)
{
    int i=0;
    while(str[i]==' ' && str [i])
        i++;
    return str[i];
}


char last_th(char *str)
{
    int i=ft_strlen(str)-1;
    while(i>0 && str[i]==' ')
        i--;
    return str[i];
}
char first_in_y(char **map,int colm,t_map_info *data)
{

    int y=0;
    while(map[y][colm]==' ' && y <data->y_map_size)
        y++;
    return map[y][colm];
}
char last_in_y(char **map,int colm,t_map_info *data)
{

    int y=data->y_map_size-1;
    while(map[y][colm]==' ' && y >-1)
        y--;
    return map[y][colm];
}



int check_walls(char **map,t_map_info *data)
{
    int x=-1;
    int y=-1;
    printf("-----------------------\n");
    while(map[++y])
    {
        x=-1;
        while(map[y][++x])
            printf("%c",map[y][x]);
        printf("-\n");
    }
    y=-1;
    while(++y < data->y_map_size)
    {
        printf("(%c) (%c)\n",first_th(map[y]),last_th(map[y]));
    }
    printf("-----------------------\n");
    x=-1;
    while(++x <data->x_map_size)
    {
        printf("(%c) (%c)\n",first_in_y(map,x,data),last_in_y(map,x,data));
        // printf("(%c) (c)\n",first_in_y(map,x));
    }
    return 0;
}

int **fillmap(char **map,t_map_info *data)
{
    int **g_map;
    g_map =malloc(sizeof(int *) * data->y_map_size);
    printf("this %d\n,",data->y_map_size);
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
            else if(map[i][j]=='0' ||map[i][j]==' ')
                g_map[i][j]=0;
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
            else
                g_map[i][j]=0;
            // printf("%d\n",g_map[i][j]);
            j++;
        }
        i++;
    }
    return g_map;

}

int cool(char **av,t_map_info *data)
{
    int shouldstop=0;
    int fd = open(av[1], O_RDONLY);
    char *g;
	g = get_next_line(fd);
    int len;
    int large=0;
    int ylen=0;
    int j;
    char *str=ft_strdup("");
    while (g)
	{
        if(shouldstop)
        {
            printf("error\n");
            exit(0);
        }
        len = ft_strlen(g);
        if(g[len-1]=='\n')
            len--;
        if(len<2 )
            shouldstop=1;
        large = MAX(len,large);
        printf("%s\n%d\n",g,len);
        str=ft_strjoin_gnl(str,g);
		free(g);
		g = get_next_line(fd);
        ylen++;
	}
    // printf("%d  %d\n",large,ylen);
    // printf("%s\n",str);

    char **map;
    char **splited = ft_split(str,'\n');
    map=malloc(sizeof(char *) * (ylen+1));
    data->y_map_size=ylen;
    data->x_map_size=large;
    int i;
    for(i =0; splited[i] ; i++)
    {
        map[i]=malloc(large+1);
        j=0;
        while(splited[i][j])
        {
            map[i][j]=splited[i][j];
            j++;
        }
        while(j<large)
        {
            map[i][j]=' ';
            j++;
        }
            map[i][j]=0;
    }
    map[i]=0;
        printf("-----------------------\n");
    for(int i =0; map[i] ; i++)
    {
        printf("%s- %zu\n",map[i],ft_strlen(map[i]));
    }
    printf("-----------------------\n");
    check_walls(map,data);
    // int **g_map;
    data->map = fillmap(map,data);
    for(int i =0; i<data->y_map_size ; i++)
    {
        for(int j =0; j<data->x_map_size ; j++)
            printf("%d ,",data->map[i][j]);
        printf("},\n{");
    }
    return 0;
}


// int main(int ac, char  **av)
// {
//     t_map_info data;
//     cool(av,&data);
//     printf("%f, %f,   %f\n",data.angle_player,data.x_player,data.y_player);
// }