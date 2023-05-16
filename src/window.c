
#include "../inc/cub3d.h"

void draw_map(t_vars *vars)
{
	int x;
	int y;

	y = -1;
	while (++y < vars->map.height)
	{
		x = -1;
		while (++x < vars->map.width)
			draw_tile(vars, y, x);
	}
}

void clean_window(t_vars *vars)
{
	for (int y = 0; y < 1024; y++)
	{
		for (int x = 0; x < 512; x++)
		{
			mlx_put_pixel(vars->img, y, x, create_color(vars->map_info.c_color.r, vars->map_info.c_color.g, vars->map_info.c_color.b, x / 2));
		}
	}

	for (int y = 0; y < 1024; y++)
	{
		for (int x = 512; x < 1024; x++)
		{
			mlx_put_pixel(vars->img, y, x, create_color(vars->map_info.f_color.r, vars->map_info.f_color.g,vars->map_info.f_color.b, x / 2 - 255) );
		}
	}
}

void draw_tile(t_vars *vars, int y, int x)
{
	int i;
	int j;
	uint32_t color_black = create_color(0, 0, 0, 255);
	uint32_t color_white = create_color(255, 255, 255, 255);
	uint32_t color_grey = create_color(160, 60, 60, 255);
	uint32_t color_blue =  create_color(66, 6, 156, 255);

	i = -1;
	while (++i < 16)
	{
		j = -1;
		while (++j < 16)
		{
			// mlx_put_pixel(vars->img, (16 * x) + i, (16 * y) + j, color_black);
			if (vars->map.map[y][x]==500)
				mlx_put_pixel(vars->img, (16 * x) + i, (16 * y) + j, color_blue);
			else if (vars->map.map[y][x]>0)
				mlx_put_pixel(vars->img, (16 * x) + i, (16 * y) + j, color_grey);
			if ((j == 15 || i == 15))
				mlx_put_pixel(vars->img, (16 * x) + i, (16 * y) + j, color_white);
		}
	}
}

void    draw_aim(t_vars *vars)
{
    put_line(vars->mlx, vars->win, 512, 506, 512, 519, create_color(0, 255, 0, 255), vars->img->width, vars->img->height);
    put_line(vars->mlx, vars->win, 506, 512, 519, 512, create_color(0, 255, 0, 255), vars->img->width, vars->img->height);
}



void draw_wal7(t_vars *vars, int r, int lineH, int32_t color)
{
	static int frame =0;
   int x1 = r * 2 + 513;
	double ligne_offset = 220 - lineH/2;
   int y1 = 220 - lineH/2;
	// Draw vertical line with specified line width
	for (int i = 0; i < 2; i++)
	{
		for (int y = y1; y <= lineH + (int)ligne_offset; y++)
		{
			mlx_put_pixel(vars->img, x1 - i, y, color);
		}
	}
}

void draw_one_sprite(t_vars *vars)
{

	static int frame =0;

	double sprite_ax;
	double sprite_ay;
	float dx;
	float dy;
	float angle;
	float angle_diff ;
	float porce_angle;
	float v_dist;
	double line_height;
	for (int i =0; i<vars->numerof_sprite ;i++)
	{
		// printf("(%s)\n",vars->sprites[i].path);
		sprite_ax=vars->sprites[i].x;
		sprite_ay=vars->sprites[i].y;
		// sprite_ay=64*i+10;
		dx = sprite_ax- vars->player.x  ;
		dy = sprite_ay -vars->player.y ;
		angle = atan2(dy, dx);
		if(angle >  vars->player.angle+PI)
				angle -= 2 * PI;
		if(angle <  vars->player.angle-PI)
				angle += 2 * PI;
		angle_diff = angle - vars->player.angle;
		porce_angle =angle_diff*180/PI;
		if(angle_diff*180/PI<=50 &&angle_diff*180/PI>=-50 )
		{
			porce_angle=(porce_angle+30)/60*512;
			v_dist = distance_to_wall(vars->player.x, vars->player.y, sprite_ax, sprite_ay, porce_angle);
			
			// printf("%f\n",v_dist);
			line_height = (64 * 600) / v_dist;
			draw_wall_5(vars,(int)porce_angle,v_dist,64*3,line_height,frame,vars->sprites[i].path);
		}
	}
		frame++;
	if(frame ==8)
		frame =0;
}

void  redraw(t_vars *vars)
{
	static int frame =1;
	char *str;
	mlx_key_data_t keydata;
	key_press_handler(keydata,vars);
	mlx_delete_image(g_vars->mlx,g_vars->weapon_img);
	clean_window(vars);		
	draw_ray(vars);
	draw_one_sprite(vars);
	if(vars->keyboard.show_map)
	{	
		draw_partcle(vars);
		draw_map(vars);
	}
	
	if(vars->player.reload)
	{

		str=ft_strjoin("./src/textures/kortas/StechkinR",ft_itoa(43-g_vars->player.reload));
		str=ft_strjoin(str,".png");
		g_vars->weapon_texture  = mlx_load_png(str);
		// printf("%s\n",str);
		// printf("%d\n",g_vars->weapon_texture);
		g_vars->weapon_img = mlx_texture_to_image(g_vars->mlx, g_vars->weapon_texture);
		mlx_image_to_window(vars->mlx,vars->weapon_img,50,257);
		mlx_delete_texture(g_vars->weapon_texture);
		free(str);
		g_vars->player.reload--;
		vars->player.shoot = 0;
	}
	else if(vars->player.shoot)
	{
		str=ft_strjoin("./src/textures/kortas/StechkinF0",ft_itoa(9-g_vars->player.shoot));
		str=ft_strjoin(str,".png");
		g_vars->weapon_texture  = mlx_load_png(str);
		g_vars->weapon_img = mlx_texture_to_image(g_vars->mlx, g_vars->weapon_texture);
		mlx_image_to_window(vars->mlx,vars->weapon_img,50,257);
		mlx_delete_texture(g_vars->weapon_texture);
		free(str);
		g_vars->player.shoot--;
	}
	else
	{
	g_vars->weapon_texture  = mlx_load_png("./src/textures/kortas/StechkinEx01.png");
	g_vars->weapon_img = mlx_texture_to_image(g_vars->mlx, g_vars->weapon_texture);
	mlx_image_to_window(vars->mlx,vars->weapon_img,50,257);
	mlx_delete_texture(g_vars->weapon_texture);
	}
	// str=ft_strjoin(": ",ft_itoa(vars->player.bullet));
	// mlx_image_to_window(vars->mlx,vars->ammo_img,800,20);
	// mlx_delete_image(vars->mlx,vars->player.print_move);
	// vars->player.print_move=mlx_put_string(vars->mlx,str,880,52);
	
	// free(str);
	frame++;
	if(frame ==9)
		frame =1;
    draw_aim(vars);
}


void	show_gun_magazine(t_vars *vars)
{
	char *str=ft_strjoin(": ",ft_itoa(vars->player.bullet));
	mlx_image_to_window(vars->mlx,vars->ammo_img,800,20);
	mlx_delete_image(vars->mlx,vars->player.print_move);
	vars->player.print_move=mlx_put_string(vars->mlx,str,880,52);
	free(str);
}


void mouse_click(mouse_key_t button, action_t action, modifier_key_t mods, void *param)
{
	t_vars *vars;
	vars = (t_vars *)param;

	if(button==0 && action == 1 && vars->player.bullet && !vars->player.reload)
	{
		vars->player.bullet--;
		vars->player.shoot=8;
		show_gun_magazine(vars);
	}
	else if(button==0 && action == 1 && !vars->player.bullet && !vars->player.reload)
	{
		vars->player.bullet=8;
		vars->player.reload=42;
		show_gun_magazine(vars);
	}


}

void render_window(t_vars *vars)
{
	int width;
	int height;

	width = vars->window_info.width;
	height = vars->window_info.height;
	vars->mlx = mlx_init(width, height, "cub3D", 1);
	if (!vars->mlx)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
		exit(1);
	}
	g_vars->player.reload=0;
	g_vars->numerof_sprite=5;
	g_vars->sprites=malloc(sizeof(t_sprite)*g_vars->numerof_sprite);
	for (int i=0; i<g_vars->numerof_sprite ; i++)
	{
		g_vars->sprites[i].x=64*i+200;
		g_vars->sprites[i].y=64*i+640;
		if(i%2==0)
			g_vars->sprites[i].path=ft_strdup("./src/textures/sprites/");
		else
			g_vars->sprites[i].path=ft_strdup("./src/textures/sprites/g");
	}
	// g_vars->wall_img = mlx_texture_to_image(g_vars->mlx, g_vars->wall_texture);
	g_vars->weapon_texture  = mlx_load_png("./src/textures/StechkinEx1.png");
	g_vars->weapon_img = mlx_texture_to_image(g_vars->mlx, g_vars->weapon_texture);
	g_vars->wall_texture  =  mlx_load_png(g_vars->map_info.NO_texure);
	g_vars->wall_texture2  = mlx_load_png(g_vars->map_info.SO_texure);
	g_vars->wall_texture3  = mlx_load_png(g_vars->map_info.WE_texure);
	g_vars->wall_texture4  = mlx_load_png(g_vars->map_info.EA_texure);
	g_vars->door_texture  = mlx_load_png("./src/textures/doorx.png");
	g_vars->enemy_texture  = mlx_load_png("./src/textures/enemy1.png");
	printf("%d %d %d %d \n",g_vars->enemy_texture->pixels[0],g_vars->enemy_texture->pixels[1],g_vars->enemy_texture->pixels[2],g_vars->enemy_texture->pixels[3]);
	g_vars->ammo_texture  = mlx_load_png("./src/textures/ammunition.png");
	g_vars->ammo_img = mlx_texture_to_image(g_vars->mlx, g_vars->ammo_texture);
	// g_vars->wall_img2 = mlx_texture_to_image(g_vars->mlx, g_vars->wall_texture);
	mlx_set_window_limit(vars->mlx, width - 200, height - 200, width, height);
	vars->img = mlx_new_image(vars->mlx, width, height);
	redraw(vars);
	mlx_set_cursor_mode(vars->mlx, vars->keyboard.cursor ? MLX_MOUSE_NORMAL : MLX_MOUSE_DISABLED);

	mlx_key_hook(vars->mlx, (mlx_keyfunc)key_press_handler_2, vars);
	
	mlx_cursor_hook(vars->mlx, (mlx_cursorfunc)mouse_handler, vars);
	mlx_mouse_hook(vars->mlx, (mlx_mousefunc)mouse_click, vars);
	mlx_image_to_window(vars->mlx, vars->img, 0, 0);
	mlx_loop_hook(vars->mlx,&loop_func,vars);
	show_gun_magazine(vars);
	mlx_loop(vars->mlx);
	
	mlx_terminate(vars->mlx);
}