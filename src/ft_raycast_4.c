/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:39:25 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/13 20:46:19 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_resize_tex_south(t_prgrm *vars, t_img *img, int x, int y)
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

void	ft_resize_tex_east(t_prgrm *vars, t_img *img, int x, int y)
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

void	ft_resize_tex_west(t_prgrm *vars, t_img *img, int x, int y)
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

void	ft_resize_door(t_prgrm *vars, t_img *img, int x, int y)
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
