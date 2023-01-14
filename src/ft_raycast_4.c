/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:39:25 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/14 18:02:45 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_resize_tex_south(t_prgrm *vars, t_img *img, int x, int y)
{
	t_img	*wall;
	int		color;

	wall = vars->img_wall_south;
	color = *(int *)(wall->addy_img + ((int)(vars->ray->texy) % \
	wall->height[0] * wall->line_length + vars->ray->texx % 64 * \
	(wall->bits_per_pixel / 8)));
	my_mlx_pixel_put(img, x, y, color);
}

void	ft_resize_tex_east(t_prgrm *vars, t_img *img, int x, int y)
{
	t_img	*wall;
	int		color;

	wall = vars->img_wall_east;
	color = *(int *)(wall->addy_img + ((int)(vars->ray->texy) % wall->height[0] \
	* wall->line_length + vars->ray->texx % 64 * (wall->bits_per_pixel / 8)));
	my_mlx_pixel_put(img, x, y, color);
}

void	ft_resize_tex_west(t_prgrm *vars, t_img *img, int x, int y)
{
	t_img	*wall;
	int		color;

	wall = vars->img_wall_west;
	color = *(int *)(wall->addy_img + ((int)(vars->ray->texy) % \
	wall->height[0] * wall->line_length + vars->ray->texx % 64 * \
	(wall->bits_per_pixel / 8)));
	my_mlx_pixel_put(img, x, y, color);
}

/*
* x: width of screen, y: height of screen
* 
*
*/
void	ft_resize_tex_north(t_prgrm *vars, t_img *img, int x, int y)
{
	t_img	*wall;
	int		color;

	wall = vars->img_wall_north;
	color = *(int *)(wall->addy_img + ((int)(vars->ray->texy) % \
	wall->height[0] * wall->line_length + vars->ray->texx % 64 * \
	(wall->bits_per_pixel / 8)));
	my_mlx_pixel_put(img, x, y, color);
}

void	ft_resize_door(t_prgrm *vars, t_img *img, int x, int y)
{
	t_img	*wall;
	int		color;

	wall = vars->img_wall_door;
	color = *(int *)(wall->addy_img + ((int)(vars->ray->texy) % \
	wall->height[0] * wall->line_length + vars->ray->texx % wall->width[0] \
	* (wall->bits_per_pixel / 8)));
	my_mlx_pixel_put(img, x, y, color);
}
