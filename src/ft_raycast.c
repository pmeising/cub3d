/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:03:05 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/04 11:03:18 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_put_floor(t_prgrm *vars)
{
	printf("vars: %s\n", vars->path_to_east);
}

void	ft_raycasting(t_prgrm *vars)
{
	ft_put_floor(vars);
}
