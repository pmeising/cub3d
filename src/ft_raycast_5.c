/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:29:50 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/23 21:47:11 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_calc_ray_dist_helper(t_prgrm *vars)
{
	if (vars->ray->side == 0)
		vars->ray->perpwalldist = (vars->ray->sidedist[0] - \
		vars->ray->deltadist[0]);
	else
		vars->ray->perpwalldist = (vars->ray->sidedist[1] - \
		vars->ray->deltadist[1]);
}

void	ft_path_exist(t_prgrm *vars)
{
	if (open(vars->path_to_north, O_RDONLY) == -1)
	{
		perror("Error\nNorth Texture does not exist.");
		vars->map_error = 3;
		ft_close_program(vars);
	}
	if (open(vars->path_to_south, O_RDONLY) == -1)
	{
		perror("Error\nSouth Texture does not exist.");
		vars->map_error = 3;
		ft_close_program(vars);
	}
	if (open(vars->path_to_east, O_RDONLY) == -1)
	{
		perror("Error\nEast Texture does not exist.");
		vars->map_error = 3;
		ft_close_program(vars);
	}
	if (open(vars->path_to_west, O_RDONLY) == -1)
	{
		perror("Error\nWest Texture does not exist.");
		vars->map_error = 3;
		ft_close_program(vars);
	}
}
