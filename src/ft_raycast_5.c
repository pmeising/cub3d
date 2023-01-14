/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 09:29:50 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/14 18:05:02 by pmeising         ###   ########.fr       */
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
