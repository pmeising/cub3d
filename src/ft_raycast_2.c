/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 20:29:57 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/14 17:28:04 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_init_raycast_2(t_prgrm *vars)
{
	if (vars->ray->rayDir[0] < 0)
	{
		vars->ray->step[0] = -1;
		vars->ray->sideDist[0] = (vars->playa[0] - vars->ray->map[0]) \
		* vars->ray->deltaDist[0];
	}
	else
	{
		vars->ray->step[0] = 1;
		vars->ray->sideDist[0] = (vars->ray->map[0] + 1.0 - vars->playa[0]) \
		* vars->ray->deltaDist[0];
	}
	if (vars->ray->rayDir[1] < 0)
	{
		vars->ray->step[1] = -1;
		vars->ray->sideDist[1] = (vars->playa[1] - vars->ray->map[1]) \
		* vars->ray->deltaDist[1];
	}
	else
	{
		vars->ray->step[1] = 1;
		vars->ray->sideDist[1] = (vars->ray->map[1] + 1.0 - vars->playa[1]) \
		* vars->ray->deltaDist[1];
	}
}

/*
* 	cameraX: x-coordinate on camera plane represented by
* 	current x-coordinate of screen - walks from x = -1 to x = 1
* 	rayDirX/rayDiry: coordinates of the ray;
*	if (vars->ray->rayDir[0] < 0) <- walk westwards
*	else <- walk easwards
*	if (vars->ray->rayDir[1] < 0) <- walk downwards
*	else <- walk upwards
*/
void	ft_init_raycast(t_prgrm *vars, int x)
{
	vars->ray->cameraX = 2 * x / (double)WIDTH - 1;
	vars->ray->rayDir[0] = vars->dir[0] + vars->camera_vector[0] \
	* vars->ray->cameraX;
	vars->ray->rayDir[1] = vars->dir[1] + vars->camera_vector[1] \
	* vars->ray->cameraX;
	vars->ray->map[0] = (int)vars->playa[0];
	vars->ray->map[1] = (int)vars->playa[1];
	if (vars->ray->rayDir[0] == 0)
		vars->ray->rayDir[0] = 1e30;
	else
		vars->ray->deltaDist[0] = fabs(1 / vars->ray->rayDir[0]);
	if (vars->ray->rayDir[1] == 0)
		vars->ray->rayDir[1] = 1e30;
	else
		vars->ray->deltaDist[1] = fabs(1 / vars->ray->rayDir[1]);
	ft_init_raycast_2(vars);
	ft_calc_ray_dist(vars);
	ft_calc_line_height(vars);
}

void	ft_calc_line_height(t_prgrm *vars)
{
	int	line_height;
	int	screen_height;

	screen_height = HEIGHT;
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
	vars->ray->line_height = line_height;
}

/*
*	side: which wall was hit
*/
void	ft_calc_ray_dist(t_prgrm *vars)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (vars->ray->sideDist[0] < vars->ray->sideDist[1])
		{
			vars->ray->sideDist[0] = vars->ray->sideDist[0] \
			+ vars->ray->deltaDist[0];
			vars->ray->map[0] += vars->ray->step[0];
			vars->ray->side = 0;
		}
		else
		{
			vars->ray->sideDist[1] += vars->ray->deltaDist[1];
			vars->ray->map[1] += vars->ray->step[1];
			vars->ray->side = 1;
		}
		if (vars->map[(int)(vars->ray->map[1])][(int)(vars->ray->map[0])] \
		== '1' || vars->map[(int)(vars->ray->map[1])][(int)(vars->ray->map[0])] \
		== 'D' || vars->map[(int)(vars->ray->map[1])][(int)(vars->ray->map[0])] \
		== 'd')
			hit = 1;
	}
	ft_calc_ray_dist_helper(vars);
}

void	ft_raycast(t_prgrm *vars)
{
	int		x;
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
