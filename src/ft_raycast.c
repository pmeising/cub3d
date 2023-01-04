/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 11:03:05 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/04 14:15:00 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_put_floor(t_prgrm *vars)
{
	int	i;

	i = 0;
	printf("vars: %s\n", vars->path_to_north);
	printf("vars: %s\n", vars->path_to_south);
	printf("vars: %s\n", vars->path_to_west);
	printf("vars: %s\n", vars->path_to_east);
	while (vars->map[i])
	{
		printf("%s\n", vars->map[i]);
		i++;
	}
}

void	ft_raycasting(t_prgrm *vars)
{
	ft_put_floor(vars);
}
