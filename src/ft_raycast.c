/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:03:05 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/08 12:26:53 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_helper_rotate(t_prgrm *vars, int i)
{
	vars->old_direction[0] = vars->direction[0];
	vars->direction[0] = vars->direction[0] * cos(i * SPEED) - vars->direction[1] * sin(i * SPEED);
	vars->direction[1] = vars->old_direction[0] * sin(i * SPEED) - vars->direction[1] * cos(i * SPEED);
	vars->old_camera_vector[0] = vars->camera_vector[0];
	vars->camera_vector[0] = vars->camera_vector[0] * cos(i * SPEED) - vars->camera_vector[1] * sin(i * SPEED);
	vars->camera_vector[1] = vars->old_camera_vector[0] * sin(i * SPEED) + vars->camera_vector[1] * cos(i * SPEED);
	ft_raycast(vars);
}

/*
* own mlx_pixel_put because original too slow;
* x/y = coordinates where to put the pixel;
*/
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dest;

	//dest = NULL;
	dest = img->addy_img + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}

/*
* W_RED = south;
* W_GREEN = north;
* W_YELLOW = west;
* W_BLUE =
*/
void	ft_put_wall(t_prgrm *vars, t_img *img, int x, int y)
{
	if (vars->direction[0] == -1 && vars->ray->side != 0 && vars->ray->cameraX < 0)
		my_mlx_pixel_put(img, x, y, W_RED / 2); // LEFT
	else if (vars->direction[0] == -1 && vars->ray->side != 0 && vars->ray->cameraX > 0)
		my_mlx_pixel_put(img, x, y, W_GREEN); // RIGHT
	else if (vars->direction[0] == -1 && vars->ray->side == 0)
		my_mlx_pixel_put(img, x, y, W_YELLOW); // FRONT
	else
		my_mlx_pixel_put(img, x, y, 0xFFFFFFFF);
}

void	ft_put_image(t_prgrm *vars, t_img *img, int x)
{
	int	y;

	y = 0;
	// printf("side: %d\n", vars->ray->side);
	// printf("dir: %f:%f\n", vars->direction[0], vars->direction[1]);
	// printf("cameraX: %f\n", vars->ray->cameraX);
	while (y < vars->ray->pos_start)
	{
		my_mlx_pixel_put(img, x, y, vars->ceiling_color);
		y++;
	}
	while(y >= vars->ray->pos_start && y <= vars->ray->pos_end)
	{
		// my_mlx_pixel_put(img, x, y, 0xFFFFFFFF);
		ft_put_wall(vars, img, x, y);
		y++;
	}
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(img, x, y, vars->floor_color);
		y++;
	}
	// printf("after my mlx pixel put for x = %d\n", x);
}

void	ft_calc_line_height(t_prgrm *vars)
{
	int	line_height;
	int	screen_height;
	
	screen_height = HEIGHT;
	// printf("perpWallDist: %f\n", vars->ray->perpWallDist);
	if (vars->ray->perpWallDist == 0)
		line_height = screen_height;
	else if (vars->ray->perpWallDist > 0 && vars->ray->perpWallDist <= 1)
		line_height = (int)screen_height;
	else
		line_height = (int)(screen_height / vars->ray->perpWallDist);
	vars->ray->pos_start = -line_height / 2 + screen_height / 2;
	if (vars->ray->pos_start < 0)
		vars->ray->pos_start = 0;
	vars->ray->pos_end = line_height / 2 + screen_height / 2;
	if (vars->ray->pos_end >= screen_height)
		vars->ray->pos_end = screen_height - 1;
}

/*
 * side: which wall was hit
*/
void	ft_calc_ray_dist(t_prgrm *vars)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (vars->ray->sideDist[0] < vars->ray->sideDist[1])
		{
			vars->ray->sideDist[0] = vars->ray->sideDist[0] + vars->ray->deltaDist[0];
			vars->ray->map[0] += vars->ray->step[0];
			vars->ray->side = 0;
		}
		else
		{
			vars->ray->sideDist[1] += vars->ray->deltaDist[1];
			vars->ray->map[1] += vars->ray->step[1];
			vars->ray->side = 1;
		}
		// printf("char **map: %c\n", vars->map[(vars->ray->map[1]) * -1][vars->ray->map[0]]);
		if (vars->map[(vars->ray->map[1]) * -1][vars->ray->map[0]] > '0')
		{
			// printf("Hit wall at position: %d, %d\n", vars->ray->map[0], vars->ray->map[1]);
			hit = 1;
		}
	}
	// printf("sideDist[0]: %f; deltaDist[0]: %f.\n", vars->ray->sideDist[0], vars->ray->deltaDist[0]);
	// printf("sideDist[1]: %f; deltaDist[1]: %f.\n", vars->ray->sideDist[1], vars->ray->deltaDist[1]);
	if (vars->ray->side == 0)
		vars->ray->perpWallDist = (vars->ray->sideDist[0] - vars->ray->deltaDist[0]);
	else
		vars->ray->perpWallDist = (vars->ray->sideDist[1] - vars->ray->deltaDist[1]);
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
	vars->ray->map[0] = (int)vars->playa[0];
	vars->ray->map[1] = (int)vars->playa[1];
	// printf("%d, %d\n", vars->ray->map[0], vars->ray->map[1]);

	if (vars->ray->rayDir[0] == 0)
		vars->ray->rayDir[0] = 1e30;
	else
		vars->ray->deltaDist[0] = fabs(1/vars->ray->rayDir[0]);
	if (vars->ray->rayDir[1] == 0)
		vars->ray->rayDir[1] = 1e30;
	else
		vars->ray->deltaDist[1] = fabs(1/vars->ray->rayDir[1]);

	if (vars->ray->rayDir[0] < 0) // walk westwards
	{
		vars->ray->step[0] = -1;
		vars->ray->sideDist[0] = (vars->playa[0] - vars->ray->map[0]) * vars->ray->deltaDist[0];
	}
	else // walk eastwards
	{
		vars->ray->step[0] = 1;
		vars->ray->sideDist[0] = (vars->ray->map[0] + 1.0 - vars->playa[0]) * vars->ray->deltaDist[0];
	}
	if (vars->ray->rayDir[1] < 0) // walk downwards
	{
		vars->ray->step[1] = -1;
		vars->ray->sideDist[1] = (vars->playa[1] - vars->ray->map[1]) * vars->ray->deltaDist[1];
	}
	else // walk upwards
	{
		vars->ray->step[1] = 1;
		vars->ray->sideDist[1] = (vars->ray->map[1] + 1.0 - vars->playa[1]) * vars->ray->deltaDist[1];
	}
	ft_calc_ray_dist(vars);
	// printf("perpWallDist at x = %d: %f\n", x, vars->ray->perpWallDist);
	ft_calc_line_height(vars);
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
	vars->ray->step = malloc(sizeof(int) * 2);
	vars->ray->step[0] = 0;
	vars->ray->step[1] = 0;
	vars->ray->perpWallDist = 0;
	vars->ray->hit = 0;
	vars->ray->side = 0;
}

void ft_init_ray_2(t_prgrm *vars, t_img *img, t_img *img_2, t_ray *ray)
{
	vars->floor_color = ft_rgb_to_hex(vars->floor_colour);
	vars->ceiling_color = ft_rgb_to_hex(vars->ceiling_colour);
	vars->img = img;
	vars->img_2 = img_2;
	img->img = mlx_new_image(vars->mlx, vars->window_width, vars->window_height);
	if (!img->img)
		printf("mlx_new_img error\n");
	img_2->img = mlx_new_image(vars->mlx, vars->window_width, vars->window_height);
		if (!img_2->img)
		printf("mlx_new_img error\n");
	img->addy_img = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
										&img->line_length, &img->endian);
	img_2->addy_img = mlx_get_data_addr(img_2->img, &img_2->bits_per_pixel, \
										&img_2->line_length, &img_2->endian);
	vars->ray = ray;
	ft_init_ray(vars);
}

void	ft_raycast(t_prgrm *vars)
{
	int	x;
	t_img	*image;

	x = 0;
	if (vars->qubit == 0)
	{
		image = vars->img; 
		vars->qubit = 1;
	}
	else
	{
		image = vars->img_2;
		vars->qubit = 0;
	}
	while (x >= 0 && x <= WIDTH)
	{
		ft_init_raycast(vars, x);
		ft_put_image(vars, image, x);
		x++;
	}
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, image->img, 0, 0);
	
}

void	ft_raycasting(t_prgrm *vars)
{
	t_img	*img;
	t_img	*img_2;
	t_ray	*ray;

	ray = malloc(sizeof(t_ray) * 1);
	ft_check(vars, ray, 3);
	img = malloc(sizeof(t_img) * 1);
	ft_check(vars, img, 3);
	img_2 = malloc(sizeof(t_img) * 1);
	ft_check(vars, img_2, 3);
	ft_init_ray_2(vars, img, img_2, ray);
	ft_raycast(vars);
}
