/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:34:40 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/14 17:21:45 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_put_image(t_prgrm *vars, t_img *img, int x)
{
	int		y;
	double	tex_pos;

	y = 0;
	find_texture_coord(vars, vars->ray->line_height);
	tex_pos = (double)((double)vars->ray->pos_start - (double)HEIGHT / 2 + (double)vars->ray->line_height / 2) * (double)vars->ray->tex_y_step;
	while (y < vars->ray->pos_start && y <= HEIGHT)
	{
		my_mlx_pixel_put(img, x, y, vars->ceiling_color);
		y++;
	}
	vars->ray->texY = (int)tex_pos & (64 - 1);
	while (y >= vars->ray->pos_start && y <= vars->ray->pos_end && y <= HEIGHT)
	{
		vars->ray->texY = (int)tex_pos & (64 - 1);
		tex_pos += vars->ray->tex_y_step;
		ft_put_wall(vars, img, x, y);
		y++;
	}
	while (y <= HEIGHT)
	{
		my_mlx_pixel_put(img, x, y, vars->floor_color);
		y++;
	}
}

void	ft_helper_rotate(t_prgrm *vars, int i)
{
	vars->old_dir[0] = vars->dir[0];
	vars->dir[0] = vars->dir[0] * cos(i * SPEED) - vars->dir[1] * \
	sin(i * SPEED);
	vars->dir[1] = vars->old_dir[0] * sin(i * SPEED) + vars->dir[1] \
	* cos(i * SPEED);
	vars->old_camera_vector[0] = vars->camera_vector[0];
	vars->camera_vector[0] = vars->camera_vector[0] * cos(i * SPEED) \
	- vars->camera_vector[1] * sin(i * SPEED);
	vars->camera_vector[1] = vars->old_camera_vector[0] * sin(i * SPEED) \
	+ vars->camera_vector[1] * cos(i * SPEED);
	ft_raycast(vars);
}

/*
* own mlx_pixel_put because original too slow;
* x/y = coordinates where to put the pixel;
*/
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dest;

	dest = img->addy_img + (y * img->line_length + x \
	* (img->bits_per_pixel / 8));
	*(unsigned int *)dest = color;
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
	if (vars->map[(int)(vars->ray->map[1])][(int)(vars->ray->map[0])] \
	== 'D' || vars->map[(int)(vars->ray->map[1])][(int)(vars->ray->map[0])] \
	== 'd')
		my_mlx_pixel_put(img, x, y, W_RED);
	else if ((vars->ray->rayDir[0] <= 0 && vars->ray->rayDir[1] <= 0 && \
	vars->ray->side == 1) || (vars->ray->rayDir[0] >= 0 && vars->ray->rayDir[1] \
	<= 0 && vars->ray->side == 1))
		ft_resize_tex_north(vars, img, x, y);
	else if ((vars->ray->rayDir[0] >= 0 && vars->ray->rayDir[1] >= 0 && \
	vars->ray->side == 1) || (vars->ray->rayDir[0] <= 0 && vars->ray->rayDir[1] \
	>= 0 && vars->ray->side == 1))
		ft_resize_tex_south(vars, img, x, y);
	else if ((vars->ray->rayDir[0] <= 0 && vars->ray->rayDir[1] <= 0 && \
	vars->ray->side == 0) || (vars->ray->rayDir[0] <= 0 && vars->ray->rayDir[1] \
	>= 0 && vars->ray->side == 0))
		ft_resize_tex_west(vars, img, x, y);
	else if ((vars->ray->rayDir[0] >= 0 && vars->ray->rayDir[1] <= 0 && \
	vars->ray->side == 0) || (vars->ray->rayDir[0] >= 0 && vars->ray->rayDir[1] \
	>= 0 && vars->ray->side == 0))
		ft_resize_tex_east(vars, img, x, y);
	else
		my_mlx_pixel_put(img, x, y, 0xFFFFFFFF);
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
	vars->ray->texX = (int)(vars->ray->WallX * (double)64);
	if ((vars->ray->side == 0 && vars->ray->rayDir[0] > 0) || \
		(vars->ray->side == 1 && vars->ray->rayDir[1] < 0))
		vars->ray->texX = 64 - vars->ray->texX - 1;
	vars->ray->tex_y_step = 1.0 * vars->img_wall_north->height[0] / vars->ray->line_height;
	(void)height;
}
