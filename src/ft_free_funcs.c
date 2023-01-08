/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:24:59 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/08 12:33:27 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_free_all(t_prgrm *vars)
{
	int	i;

	i = 0;
	//freeing the vars struct direct mallocs
	ft_free(vars->playa);
	ft_free(vars->direction);
	ft_free(vars->old_direction);
	ft_free(vars->camera_vector);
	ft_free(vars->old_camera_vector);
	ft_free(vars->path_to_map);
	ft_free(vars->path_to_north);
	ft_free(vars->path_to_south);
	ft_free(vars->path_to_west);
	ft_free(vars->path_to_east);
	ft_free(vars->floor_colour);
	ft_free(vars->ceiling_colour);
	while (vars->map[i] != NULL)
	{
		ft_free (vars->map[i]);
		i++;
	}
	ft_free(vars->map);
	
	// freeing the img structs
	mlx_destroy_image(vars->mlx, vars->img->img);
	ft_free(vars->img);
	mlx_destroy_image(vars->mlx, vars->img_2->img);
	ft_free(vars->img_2);

	// freeing ray struct	
	ft_free(vars->ray->rayDir);
	ft_free(vars->ray->map);
	ft_free(vars->ray->deltaDist);
	ft_free(vars->ray->sideDist);
	ft_free(vars->ray->step);
	ft_free(vars->ray);
	
}

void	ft_free(void *cont)
{
	if (cont)
	{
		free (cont);
		cont = NULL;
	}
}

int	ft_close_program(t_prgrm *vars)
{
	ft_free_all(vars);
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	mlx_destroy_display(vars->mlx);
	ft_free(vars->mlx);
	free (vars);
	exit(0);
	return (1);
}
