/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:29:50 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/14 09:31:14 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_calc_ray_dist_helper(t_prgrm *vars)
{
	if (vars->ray->side == 0)
		vars->ray->perpWallDist = (vars->ray->sideDist[0] - \
		vars->ray->deltaDist[0]);
	else
		vars->ray->perpWallDist = (vars->ray->sideDist[1] - \
		vars->ray->deltaDist[1]);
}
