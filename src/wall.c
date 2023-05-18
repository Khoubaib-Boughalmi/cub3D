#include "../inc/cub3d.h"

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