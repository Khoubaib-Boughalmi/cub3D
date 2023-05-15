/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kboughal < kboughal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 12:48:02 by aechaoub          #+#    #+#             */
/*   Updated: 2023/05/15 17:15:11 by kboughal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 6

# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <fcntl.h>
# include <math.h>
// # include "../mlx/mlx.h"

typedef struct s_vars
{
	void	*pht;
	char	*adr;
	int		img_width;
	int		img_height;
	int		y;
	int		x;
	int		many;
	int		yplace;
	int		xplace;
}	t_img;

typedef struct s_map
{
	int	**map;
	int	y;
	int	x;
	int	ystart;
	int	xstart;
}	t_map;

typedef struct s_val
{
	int	i;
	int	j;
}	t_val;

typedef struct s_data
{
	t_img	gras;
	t_img	small;
	t_img	lol;
	t_img	mywin;
	t_img	dollar;
	t_img	door;
	t_img	enemy;
	t_map	map;
	void	*img;
	void	*mlx;
	void	*win;
	char	**frame_coins;
	char	**frame_enemy;
	int		stillplay;
}	t_data;

char	*ft_itoa(int n);
void	exitfunc(t_data *mapty);
void	free_tab(int **tab, int j);
void	ft_putnbr(int n);
void	ft_putstr(char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	planmap(int **tab, int x, int y);
char	*get_next_line(int fd);
char	*ft_strdup(const char *str);
char	*ft_substr2(char *s, unsigned int start, size_t len);
char	*ft_strjoin_gnl(char *s1, char *s2);
void	ft_bzero(void *str, size_t n);
size_t	ft_strlen(const char *str);
void	getrslt(t_data *mapty, char *av);
char	**ft_split(char const *s, char c);
void	callimage(t_data *img);
void	callimage_1_puststrs(t_data *img, int i, int j);
void	callimage_1(t_data *img);
void	callimage_2(t_data *img);
void	check_images(t_data *img);
void	key_hook_1(int keycode, t_data *vars);
void	moveright(t_data *img, int nt);
void	moveleft(t_data *img, int nt);
void	movedown(t_data *img, int nt);
void	moveup(t_data *img, int nt);
int		destroy(t_data *vars);
int		**add_toarr(t_data *mapty, char *av);
void	addsecend_toarr(t_data *mapty, char *av, int **map);
void	checkext(char *av);
int		key_hook(int keycode, t_data *vars);
#endif
