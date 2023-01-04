/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:03:05 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/04 21:53:13 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
* own mlx_pixel_put because original too slow;
* x/y = coordinates where to put the pixel;
*/
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dest;

	dest = NULL;
	dest = img->addy_img + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}

void	ft_put_image(t_prgrm *vars, t_img *img)
{
	int	y;
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < (HEIGHT) / 2)
		{
			my_mlx_pixel_put(img, x, y, 0xFFFFFFFF);
			y++;
		}
		// while(y > BLA && y < BLI)
		// {
		// 	my_mlx_pixel_put(img_2, x, y, 0xFFFFFFFF);
		// 	y++;
		// }
		while (y < HEIGHT)
		{
			my_mlx_pixel_put(img, x, y, 0xFFF00000);
			y++;
		}
		x++;
	}
	printf("after my mlx pixel put\n");
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, img->img, 0, 0);
}

/*
* cameraX: x-coordinate on camera plane represented by
* current x-coordinate of screen;
* rayDirX/rayDiry: coordinates of the ray; 
*/
void ft_init_raycast(t_prgrm *vars, int x)
{
	vars->ray->cameraX = 2 * x / (double)WIDTH - 1; // walks from x = -1 to x = 1
	vars->ray->rayDir[0] = vars->direction[0] + vars->camera_vector[0] * vars->ray->cameraX;
	vars->ray->rayDir[1] = vars->direction[1] + vars->camera_vector[1] * vars->ray->cameraX;
	vars->ray->map[0] = vars->playa[0];
	vars->ray->map[0] = vars->playa[1];
	if (vars->ray->rayDir[0] == 0)
		vars->ray->rayDir[0] = 1e30;
	if (vars->ray->rayDir[1] == 0)
		vars->ray->rayDir[1] = 1e30;
	vars->ray->deltaDist[0] = fabs(1/vars->ray->rayDir[0]);
	vars->ray->deltaDist[1] = fabs(1/vars->ray->rayDir[1]);
	if (vars->ray->rayDir[0] < 0)
	{
		vars->ray->step[0] = -1;
		vars->ray->sideDist[0] = (vars->playa[0] - vars->ray->map[0]) * vars->ray->deltaDist[0];
	}
	else
	{
		vars->ray->step[0] = 1;
		vars->ray->sideDist[0] = (vars->ray->map[0] + 1.0 - vars->playa[0]) * vars->ray->deltaDist[0];
	}
	if (vars->ray->rayDir[1] < 0)
	{
		vars->ray->step[1] = -1;
		vars->ray->sideDist[1] = (vars->playa[1] - vars->ray->map[1]) * vars->ray->deltaDist[1];
	}
	else
	{
		vars->ray->step[1] = 1;
		vars->ray->sideDist[1] = (vars->ray->map[1] + 1.0 - vars->playa[1]) * vars->ray->deltaDist[1];
	}
}

void	ft_init_ray(t_prgrm *vars)
{
	vars->ray->rayDir = malloc(sizeof(double) * 2);
	vars->ray->rayDir[0] = 0;
	vars->ray->rayDir[1] = 1;
	vars->ray->map = malloc(sizeof(int) * 2);
	vars->ray->map[0] = 0;
	vars->ray->map[1] = 0;
	vars->ray->deltaDist = malloc(sizeof(double) * 2);
	vars->ray->deltaDist[0] = 0;
	vars->ray->deltaDist[1] = 0;
	vars->ray->sideDist = malloc(sizeof(double) * 2);
	vars->ray->sideDist[0] = 0;
	vars->ray->sideDist[1] = 0;
	vars->ray->perpWallDist = 0;
	vars->ray->step = malloc(sizeof(int) * 2);
	vars->ray->step[0] = 0;
	vars->ray->step[1] = 0;
	vars->ray->hit = 0;
	vars->ray->side = 0;
}

void	ft_raycasting(t_prgrm *vars)
{
	t_img	*img;
	t_img	*img_2;
	t_ray	*ray;
	int		x;
	
	x = 0;
	ray = malloc(sizeof(t_ray) * 1);
	img = malloc(sizeof(t_img) * 1);
	img_2 = malloc(sizeof(t_img) * 1);
	vars->img = img;
	vars->img_2 = img_2;
	vars->ray = ray;
	ft_init_ray(vars);
	if (!img)
		printf("img malloc error\n");
	img_2->img = mlx_new_image(vars->mlx, vars->window_width, vars->window_height);
	img->img = mlx_new_image(vars->mlx, vars->window_width, vars->window_height);
	if (!img->img)
		printf("mlx_new_img error\n");
	img_2->addy_img = mlx_get_data_addr(img_2->img, &img_2->bits_per_pixel, \
										&img_2->line_length, &img_2->endian);
	img->addy_img = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
										&img->line_length, &img->endian);
	if (!img->addy_img)
		printf("no img addy error\n");
	ft_put_image(vars, img);
	while (x < WIDTH)
	{
		ft_init_raycast(vars, x);
		// ft_calc_ray(vars);
		x++;
	}
}
