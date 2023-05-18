#include "../inc/cub3d.h"

void draw_wall(t_vars *vars, double r,double rx,double ry, double lineH,int hororver)
{
	mlx_texture_t *imgtxet;
	int32_t color;
	double porcentsage;
   if(hororver==1 )
	porcentsage=ry/64;
   if(hororver==0 )
	porcentsage=rx/64;
	int x1 = r * 2 + 2;
	int k=lineH;
	if (lineH > 1020)
			lineH = 1020;
	int ligne_offset = 512 - lineH / 2;
	int y1 = 512 - lineH / 2;
	float y2 =  (float)(k / 2 - 512)/k*512;
	if(y2<0)
		y2=0;
	porcentsage-=(int)porcentsage;
	imgtxet=vars->NO_wall_texture_texture;
	if(vars->map.map[(int)floor(ry/64)][(int)floor(rx/64)]==500)
	{
		imgtxet=vars->door_texture;
		
	}
   else if(hororver==0 )
   {

	if(vars->player.y>ry)
		imgtxet=vars->NO_wall_texture_texture;
	else
		imgtxet=vars->SO_wall_texture;
	// imgtxet=vars->SO_wall_texture;
	if(vars->player.angle<PI)
	   porcentsage=1-porcentsage;
   }
   else if(hororver==1 )
   {
	if(vars->player.x>rx)
		imgtxet=vars->EA_wall_texture;
	else
		imgtxet=vars->WE_wall_texture;
	// imgtxet=vars->SO_wall_texture;
	if (vars->player.angle>PI/2 && vars->player.angle<3*PI/2)
	   porcentsage=1-porcentsage;
   }
   int theline=(int)(porcentsage*512)*4;
	float  g=(float)512/k;
	float  rl=0;
	int in=0;

	for (int i = 0; i < 2; i++)
	{
		in=0;
		rl=y2;
		for (int y = y1 - 2; y <= lineH + (int)ligne_offset && y < 1023; y++)
		{
			in=512*4*(int)floor(rl);
			// printf("%d %d \n",theline+in,imgtxet->height*imgtxet->width*4);
			if(theline+in<(int)imgtxet->height*(int)imgtxet->width*4)
				color =create_color(imgtxet->pixels[(theline)+in],imgtxet->pixels[(theline)+in+1], imgtxet->pixels[(theline)+in+2],imgtxet->pixels[(theline)+in+3]);
			else
				color=create_color(0,0,0,0);
			mlx_put_pixel(vars->img, x1 - i, y, color);
			rl+=g;
		}
	}
}

int ff=0;

void draw_the_sprite(t_vars *vars, double r,double distance, double lineH,int frame,char *sprite_path)
{
	mlx_texture_t *imgtxet;
	int32_t trans=create_color(0,0,0,0);;
	int32_t color;
	int x1 = r * 2 + 2;
	if (lineH > 1020)
			lineH = 1020;
	int ligne_offset = 512 - lineH / 2.9;
	int y1 = 512 - lineH / 2.9;
	float por_h = 608/lineH;
	float tot_h=0;
	float por_v = 160/(4*lineH/10);
	float tot_v=0;
	char *str;
	char *tmp;
	
	tmp=ft_itoa(frame/2);
	str=ft_strjoin(sprite_path,tmp);
	free(tmp);
	tmp=str;
	// printf("%s\n",str);
	str=ft_strjoin(str,".png");
	imgtxet= mlx_load_png(str);
	free(tmp);
	free(str);
	int time=r -(lineH/10);
	if(time<0)
	{
		tot_v+=abs(time*2)*por_v;
		time =0;

	}
	int lol=0;
	int suu=0;
	while(time <r +(lineH/10) && time <512)
	{
		if(distance<g_ray_ds[time])
		{
			g_ray_ds[time ]=distance;
		x1 = time* 2 + 2;
			for (int i = 0; i < 2; i++)
			{
				tot_h=0;
				suu=(int)tot_v;
				suu*=4;
				lol=(int)(tot_h*160*4)+suu;
				for (int y = y1; y <= lineH + (int)ligne_offset &&  y <1024; y++)
				{
					if(lol<(int)imgtxet->height*(int)imgtxet->width *4)
						color =create_color(imgtxet->pixels[lol],imgtxet->pixels[lol+1], imgtxet->pixels[lol+2],imgtxet->pixels[lol+3]);
				if(color !=trans )
					mlx_put_pixel(vars->img, x1 - i, y, color);
					tot_h+=por_h;
					lol = (int)tot_h*160*4+suu;
				}
				tot_v+=por_v;
			}
		}
		else
				tot_v+=2*por_v;
		time++;
	}
	mlx_delete_texture(imgtxet);
}