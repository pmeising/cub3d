/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:03:05 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/13 14:09:39 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_helper_rotate(t_prgrm *vars, int i)
{
	vars->old_direction[0] = vars->direction[0];
	vars->direction[0] = vars->direction[0] * cos(i * SPEED) - vars->direction[1] * sin(i * SPEED);
	vars->direction[1] = vars->old_direction[0] * sin(i * SPEED) + vars->direction[1] * cos(i * SPEED);
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

	dest = img->addy_img + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dest = color;
}

	// unsigned int	color;
	// // int				tex_y;
	// int				height;

	// height = vars->ray->pos_end - vars->ray->pos_start;
	// color = *(int *)(vars->img_wall_north->addy_img + (int)(height % 64 * (img->bits_per_pixel / 8)));
	// // printf("color: %d\n", color);
	// my_mlx_pixel_put(img, x, y, color);

void ft_resize_tex_south(t_prgrm *vars, t_img *img, int x, int y)
{
	char	*tex_addr;
	int		height;
	t_img	*wall;
	int		color;

	height = vars->ray->pos_end - vars->ray->pos_start;
	wall = vars->img_wall_south;
	tex_addr = NULL;
	tex_addr = wall->addy_img + ((int)(vars->ray->texY) % 64 * height + vars->ray->texX % 64 * (wall->bits_per_pixel / 8));
	color = *(int *)tex_addr;
	my_mlx_pixel_put(img, x, y, color);
	vars->ray->texY = vars->ray->texY + vars->ray->tex_y_step;
}

void ft_resize_door(t_prgrm *vars, t_img *img, int x, int y)
{
	char	*tex_addr;
	int		height;
	t_img	*wall;
	int		color;

	height = vars->ray->pos_end - vars->ray->pos_start;
	wall = vars->img_wall_door;
	tex_addr = NULL;
	tex_addr = wall->addy_img + ((int)(vars->ray->texY) % 274 * height + vars->ray->texX % 274 * (wall->bits_per_pixel / 8));
	color = *(int *)tex_addr;
	my_mlx_pixel_put(img, x, y, color);
	vars->ray->texY = vars->ray->texY + vars->ray->tex_y_step;
}

void ft_resize_tex_east(t_prgrm *vars, t_img *img, int x, int y)
{
	char	*tex_addr;
	int		height;
	t_img	*wall;
	int		color;

	height = vars->ray->pos_end - vars->ray->pos_start;
	wall = vars->img_wall_east;
	tex_addr = NULL;
	tex_addr = wall->addy_img + ((int)(vars->ray->texY) % 64 * height + vars->ray->texX % 64 * (wall->bits_per_pixel / 8));
	color = *(int *)tex_addr;
	my_mlx_pixel_put(img, x, y, color);
	vars->ray->texY = vars->ray->texY + vars->ray->tex_y_step;
}

void ft_resize_tex_west(t_prgrm *vars, t_img *img, int x, int y)
{
	char	*tex_addr;
	int		height;
	t_img	*wall;
	int		color;

	height = vars->ray->pos_end - vars->ray->pos_start;
	wall = vars->img_wall_west;
	tex_addr = NULL;
	tex_addr = wall->addy_img + ((int)(vars->ray->texY) % 64 * height + vars->ray->texX % 64 * (wall->bits_per_pixel / 8));
	color = *(int *)tex_addr;
	my_mlx_pixel_put(img, x, y, color);
	vars->ray->texY = vars->ray->texY + vars->ray->tex_y_step;
}

/*
* x: width of screen, y: height of screen
* 
*
*/
void	ft_resize_tex_north(t_prgrm *vars, t_img *img, int x, int y)
{
	char	*tex_addr;
	int		height;
	t_img	*wall;
	int		color;

	height = vars->ray->pos_end - vars->ray->pos_start;
	wall = vars->img_wall_north;
	tex_addr = NULL;
	tex_addr = wall->addy_img + ((int)(vars->ray->texY) % 64 * height + vars->ray->texX % 64 * (wall->bits_per_pixel / 8));
	color = *(int *)tex_addr;
	// printf("%d at y: %d\n", color, y);
	my_mlx_pixel_put(img, x, y, color);
	vars->ray->texY = vars->ray->texY + vars->ray->tex_y_step;
}

/*
*	W_RED = EAST;
* 	W_GREEN = SOUTH;
*	W_YELLOW = WEST;
* 	W_BLUE = NORTH;
*	N{0, 1}
*	S{0,-1}
*	W{-1,0}
*	E{1, 0}
*/
void	ft_put_wall(t_prgrm *vars, t_img *img, int x, int y)
{
	// printf("y: %d\n", y);
	if (vars->map[(int)(vars->ray->map[1])][(int)(vars->ray->map[0])] == 'D' || vars->map[(int)(vars->ray->map[1])][(int)(vars->ray->map[0])] == 'd')
		my_mlx_pixel_put(img, x, y, W_RED); // DOOR
	else if (vars->ray->rayDir[0] <= 0 && vars->ray->rayDir[1] <= 0 && vars->ray->side == 1)
		ft_resize_tex_north(vars, img, x, y);
		// my_mlx_pixel_put(img, x, y, W_BLUE / 2); // NORTH
	else if (vars->ray->rayDir[0] >= 0 && vars->ray->rayDir[1] <= 0 && vars->ray->side == 1)
		ft_resize_tex_north(vars, img, x, y);
		// my_mlx_pixel_put(img, x, y, W_BLUE / 2); // NORTH
	else if (vars->ray->rayDir[0] >= 0 && vars->ray->rayDir[1] >= 0 && vars->ray->side == 1)
		ft_resize_tex_south(vars, img, x, y);
		// my_mlx_pixel_put(img, x, y, W_GREEN / 2); // SOUTH
	else if (vars->ray->rayDir[0] <= 0 && vars->ray->rayDir[1] >= 0 && vars->ray->side == 1)
		ft_resize_tex_south(vars, img, x, y);
		// my_mlx_pixel_put(img, x, y, W_GREEN / 2); // SOUTH
	else if (vars->ray->rayDir[0] <= 0 && vars->ray->rayDir[1] <= 0 && vars->ray->side == 0)
		ft_resize_tex_west(vars, img, x, y);
		// my_mlx_pixel_put(img, x, y, W_YELLOW / 2); // WEST
	else if (vars->ray->rayDir[0] <= 0 && vars->ray->rayDir[1] >= 0 && vars->ray->side == 0)
		ft_resize_tex_west(vars, img, x, y);
		// my_mlx_pixel_put(img, x, y, W_YELLOW / 2); // WEST
	else if (vars->ray->rayDir[0] >= 0 && vars->ray->rayDir[1] <= 0 && vars->ray->side == 0)
		ft_resize_tex_east(vars, img, x, y);
		// my_mlx_pixel_put(img, x, y, W_RED / 2); // EAST
	else if (vars->ray->rayDir[0] >= 0 && vars->ray->rayDir[1] >= 0 && vars->ray->side == 0)
		ft_resize_tex_east(vars, img, x, y);
		// my_mlx_pixel_put(img, x, y, W_RED / 2); // EAST
	else
	{
		my_mlx_pixel_put(img, x, y, 0xFFFFFFFF);
	}
}

void	find_texture_coord(t_prgrm *vars, int height)
{
	if (vars->ray->side == 0)
		vars->ray->WallX = vars->playa[1] + vars->ray->perpWallDist * \
			vars->ray->rayDir[1];
	else
		vars->ray->WallX = vars->playa[0] + vars->ray->perpWallDist * \
			vars->ray->rayDir[0];
	vars->ray->WallX -= floor(vars->ray->WallX);
	vars->ray->texX = (int)(vars->ray->WallX * (double)64/*wall_tex->width*/);
	if ((vars->ray->side == 0 && vars->ray->rayDir[0] > 0) || \
		(vars->ray->side == 1 && vars->ray->rayDir[1] < 0))
		vars->ray->texX = 64 - vars->ray->texX;
	vars->ray->tex_y_step = 64/*wall_tex->height*/ / (double)height;
	vars->ray->texY = 0;
	if (height > HEIGHT)
		vars->ray->texY = (height - HEIGHT) * \
			vars->ray->tex_y_step / 2;
}

// if (vars->ray->side == 0)
	// 	wallX = vars->playa[1] + vars->ray->perpWallDist * vars->ray->rayDir[1];
	// else
	// 	wallX = vars->playa[0] + vars->ray->perpWallDist * vars->ray->rayDir[0];
	// wallX -= floor((wallX));

	// vars->ray->texX = (int)(wallX * (double)64);
	// if (vars->ray->side == 0 && vars->ray->rayDir[0] > 0)
	// 	vars->ray->texX = 64 - vars->ray->texX;
	// else if (vars->ray->side == 1 && vars->ray->rayDir[1] < 0)
	// 	vars->ray->texX = 64 - vars->ray->texX;
	// step = 64 / (double)height;
	// double texPos;
	// texPos = (vars->ray->pos_start - HEIGHT /*height*/ / 2 + height / 2) * step;
	//int m;
	// m = vars->ray->pos_start;
	
void	ft_put_image(t_prgrm *vars, t_img *img, int x)
{
	int		height;
	int	y;

	height = vars->ray->pos_end - vars->ray->pos_start;
	y = 0;
	find_texture_coord(vars, height);
	while (y < vars->ray->pos_start && y <= HEIGHT)
	{
		my_mlx_pixel_put(img, x, y, vars->ceiling_color);
		y++;
	}
	// printf("built sky x: %d. y: %d\n", x, y);
	while(y >= vars->ray->pos_start && y <= vars->ray->pos_end && y <= HEIGHT)
	{
		ft_put_wall(vars, img, x, y);
		y++;
	}
	// printf("built wall. x: %d. y: %d\n", x, y);
	while (y <= HEIGHT)
	{
		my_mlx_pixel_put(img, x, y, vars->floor_color);
		y++;
	}
}
	// --------------------
// 	if (vars->ray->side == 0)
// 		wallX = vars->playa[1] + vars->ray->perpWallDist * vars->ray->rayDir[1];
// 	else
// 		wallX = vars->playa[0] + vars->ray->perpWallDist * vars->ray->rayDir[0];
// 	wallX -= floor((wallX));
// 	vars->ray->texX = (int)(wallX * (double)img->width[0]);
	
// 	if (vars->ray->side == 0 && vars->ray->rayDir[0] > 0)
// 		vars->ray->texX = img->width[0] - vars->ray->texX - 1;
// 	if (vars->ray->side == 1 && vars->ray->rayDir[1] < 0)
// 		vars->ray->texX = img->width[0] - vars->ray->texX - 1;
// 	step = (double)img->height[0] / (double)height; // lineheight;
	
// }

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
*	side: which wall was hit
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
		if (vars->map[(int)(vars->ray->map[1])][(int)(vars->ray->map[0])] == '1' || vars->map[(int)(vars->ray->map[1])][(int)(vars->ray->map[0])] == 'D' || vars->map[(int)(vars->ray->map[1])][(int)(vars->ray->map[0])] == 'd')
			hit = 1;
	}
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
	// printf("%f, %f\n", vars->ray->map[0], vars->ray->map[1]);

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
	// vars->ray->map[0] = (int)vars->playa[0];
	// vars->ray->map[1] = (int)vars->playa[1];
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
	vars->ray->map[0] = (int)vars->playa[0];
	vars->ray->map[1] = (int)vars->playa[1];
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
	// print_map(vars);
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
	// x = 500;
	while (x >= 0 && x <= WIDTH)
	{
		ft_init_raycast(vars, x);
		ft_put_image(vars, image, x);
		x++;
	}
	// printf("side: %d\n", vars->ray->side);
	// printf("dir: %f:%f\n", vars->direction[0], vars->direction[1]);
	// printf("cameraX: %f\n", vars->ray->cameraX);
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, image->img, 0, 0);
	
}

void ft_init_img(t_prgrm *vars)
{
	vars->img_wall_north = malloc(sizeof(t_img) * 1);
	ft_check(vars, vars->img_wall_north, 3);
	vars->img_wall_north->height[0] = 0;
	vars->img_wall_north->width[0] = 0;
	vars->img_wall_south = malloc(sizeof(t_img) * 1);
	ft_check(vars, vars->img_wall_south, 3);
	vars->img_wall_east = malloc(sizeof(t_img) * 1);
	ft_check(vars, vars->img_wall_east, 3);
	vars->img_wall_west = malloc(sizeof(t_img) * 1);
	ft_check(vars, vars->img_wall_west, 3);
	vars->img_wall_north->img = mlx_xpm_file_to_image(vars->mlx, "./images/wall_1.xpm", vars->img_wall_north->width, vars->img_wall_north->height);
	vars->img_wall_south->img = mlx_xpm_file_to_image(vars->mlx, "./images/wall_2.xpm", vars->img_wall_south->width, vars->img_wall_south->height);
	vars->img_wall_east->img = mlx_xpm_file_to_image(vars->mlx, "./images/wall_3.xpm", vars->img_wall_east->width, vars->img_wall_east->height);
	vars->img_wall_west->img = mlx_xpm_file_to_image(vars->mlx, "./images/wall_4.xpm", vars->img_wall_west->width, vars->img_wall_west->height);
	vars->img_wall_north->addy_img = mlx_get_data_addr(vars->img_wall_north->img ,&vars->img_wall_north->bits_per_pixel, &vars->img_wall_north->line_length, &vars->img_wall_north->endian);
	vars->img_wall_south->addy_img = mlx_get_data_addr(vars->img_wall_south->img ,&vars->img_wall_south->bits_per_pixel, &vars->img_wall_south->line_length, &vars->img_wall_south->endian);
	vars->img_wall_west->addy_img = mlx_get_data_addr(vars->img_wall_west->img ,&vars->img_wall_west->bits_per_pixel, &vars->img_wall_west->line_length, &vars->img_wall_west->endian);
	vars->img_wall_east->addy_img = mlx_get_data_addr(vars->img_wall_east->img ,&vars->img_wall_east->bits_per_pixel, &vars->img_wall_east->line_length, &vars->img_wall_east->endian);
	printf("%p\n", vars->img_wall_north->addy_img);
}

void	ft_raycasting(t_prgrm *vars)
{
	t_img	*img;
	t_img	*img_2;
	t_ray	*ray;
	
	ft_init_img(vars);
	ray = malloc(sizeof(t_ray) * 1);
	ft_check(vars, ray, 3);
	img = malloc(sizeof(t_img) * 1);
	ft_check(vars, img, 3);
	img_2 = malloc(sizeof(t_img) * 1);
	ft_check(vars, img_2, 3);
	// print_map(vars);
	ft_init_ray_2(vars, img, img_2, ray);
}
