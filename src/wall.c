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
	float y2 =  (float)(k / 2 - 512)/k*64;
	if(y2<0)
		y2=0;

	porcentsage-=(int)porcentsage;
	imgtxet=vars->wall_texture;
   if(hororver==0 )
   {

	if(vars->player.y>ry)
		imgtxet=vars->wall_texture3;
	else
		imgtxet=vars->wall_texture4;	
	// imgtxet=vars->wall_texture2;
	if(vars->player.angle<PI)
	   porcentsage=1-porcentsage;
   }
   if(hororver==1 )
   {
	if(vars->player.x>rx)
		imgtxet=vars->wall_texture2;
	// imgtxet=vars->wall_texture2;
	if (vars->player.angle>PI/2 && vars->player.angle<3*PI/2)
	   porcentsage=1-porcentsage;
   }
   int theline=(int)(porcentsage*64)*4;
	float  g=(float)64/k;
	float  rl=0;
	int in=0;

	for (int i = 0; i < 2; i++)
	{
		in=0;
		rl=y2;
		for (int y = y1; y < lineH + (int)ligne_offset - 1; y++)
		{
			in=64*4*(int)floor(rl);
			color =create_color(imgtxet->pixels[(theline)+in],imgtxet->pixels[(theline)+in+1], imgtxet->pixels[(theline)+in+2],imgtxet->pixels[(theline)+in+3]);
			mlx_put_pixel(vars->img, x1 - i - 1, y, color);
			rl+=g;
		}
	}
}