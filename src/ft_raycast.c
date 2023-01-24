/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:03:05 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/16 15:08:50 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_init_ray_2(t_prgrm *vars)
{
	vars->ray->raydir = malloc(sizeof(double) * 2);
	vars->ray->raydir[0] = 0;
	vars->ray->raydir[1] = 1;
	vars->ray->map = malloc(sizeof(int) * 2);
	vars->ray->map[0] = 0;
	vars->ray->map[1] = 0;
	vars->ray->deltadist = malloc(sizeof(double) * 2);
	vars->ray->deltadist[0] = 0;
	vars->ray->deltadist[1] = 0;
	vars->ray->sidedist = malloc(sizeof(double) * 2);
	vars->ray->sidedist[0] = 0;
	vars->ray->sidedist[1] = 0;
	vars->ray->step = malloc(sizeof(int) * 2);
	vars->ray->step[0] = 0;
	vars->ray->step[1] = 0;
	vars->ray->perpwalldist = 0;
	vars->ray->hit = 0;
	vars->ray->side = 0;
	vars->ray->map[0] = (int)vars->playa[0];
	vars->ray->map[1] = (int)vars->playa[1];
}

void	ft_init_ray(t_prgrm *vars, t_img *img, t_img *img_2, t_ray *ray)
{
	vars->floor_color = ft_rgb_to_hex(vars->floor_colour);
	vars->ceiling_color = ft_rgb_to_hex(vars->ceiling_colour);
	vars->img = img;
	vars->img_2 = img_2;
	img->img = mlx_new_image(vars->mlx, vars->window_width, \
	vars->window_height);
	if (!img->img)
		printf("mlx_new_img error\n");
	img_2->img = mlx_new_image(vars->mlx, vars->window_width, \
	vars->window_height);
	if (!img_2->img)
		printf("mlx_new_img error\n");
	img->addy_img = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
	&img->line_length, &img->endian);
	img_2->addy_img = mlx_get_data_addr(img_2->img, &img_2->bits_per_pixel, \
	&img_2->line_length, &img_2->endian);
	vars->ray = ray;
	ft_init_ray_2(vars);
}

void	ft_init_img_2(t_prgrm *vars)
{
	vars->img_wall_door->img = mlx_xpm_file_to_image(vars->mlx, \
	"./images/scifi_64.xpm", vars->img_wall_door->width, \
	vars->img_wall_door->height);
	vars->img_wall_north->addy_img = mlx_get_data_addr(\
	vars->img_wall_north->img, &vars->img_wall_north->bits_per_pixel, \
	&vars->img_wall_north->line_length, &vars->img_wall_north->endian);
	vars->img_wall_south->addy_img = mlx_get_data_addr(\
	vars->img_wall_south->img, &vars->img_wall_south->bits_per_pixel, \
	&vars->img_wall_south->line_length, &vars->img_wall_south->endian);
	vars->img_wall_west->addy_img = mlx_get_data_addr(\
	vars->img_wall_west->img, &vars->img_wall_west->bits_per_pixel, \
	&vars->img_wall_west->line_length, &vars->img_wall_west->endian);
	vars->img_wall_east->addy_img = mlx_get_data_addr(\
	vars->img_wall_east->img, &vars->img_wall_east->bits_per_pixel, \
	&vars->img_wall_east->line_length, &vars->img_wall_east->endian);
	vars->img_wall_door->addy_img = mlx_get_data_addr(\
	vars->img_wall_door->img, &vars->img_wall_door->bits_per_pixel, \
	&vars->img_wall_door->line_length, &vars->img_wall_door->endian);
}

void	ft_init_img(t_prgrm *vars)
{
	vars->img_wall_north = malloc(sizeof(t_img) * 1);
	ft_check(vars, vars->img_wall_north, 3);
	vars->img_wall_south = malloc(sizeof(t_img) * 1);
	ft_check(vars, vars->img_wall_south, 3);
	vars->img_wall_east = malloc(sizeof(t_img) * 1);
	ft_check(vars, vars->img_wall_east, 3);
	vars->img_wall_west = malloc(sizeof(t_img) * 1);
	ft_check(vars, vars->img_wall_west, 3);
	vars->img_wall_door = malloc(sizeof(t_img) * 1);
	ft_check(vars, vars->img_wall_door, 3);
	vars->img_wall_north->img = mlx_xpm_file_to_image(vars->mlx, \
	vars->path_to_north, vars->img_wall_north->width, \
	vars->img_wall_north->height);
	vars->img_wall_south->img = mlx_xpm_file_to_image(vars->mlx, \
	vars->path_to_south, vars->img_wall_south->width, \
	vars->img_wall_south->height);
	vars->img_wall_east->img = mlx_xpm_file_to_image(vars->mlx, \
	vars->path_to_east, vars->img_wall_east->width, \
	vars->img_wall_east->height);
	vars->img_wall_west->img = mlx_xpm_file_to_image(vars->mlx, \
	vars->path_to_west, vars->img_wall_west->width, \
	vars->img_wall_west->height);
	ft_init_img_2(vars);
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
	ft_init_ray(vars, img, img_2, ray);
}
