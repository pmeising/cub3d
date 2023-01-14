/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:24:59 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/14 10:54:50 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_free_all_2(t_prgrm *vars)
{
	mlx_destroy_image(vars->mlx, vars->img_2->img);
	ft_free(vars->img_2);
	mlx_destroy_image(vars->mlx, vars->img_wall_north->img);
	ft_free(vars->img_wall_north);
	mlx_destroy_image(vars->mlx, vars->img_wall_south->img);
	ft_free(vars->img_wall_south);
	mlx_destroy_image(vars->mlx, vars->img_wall_east->img);
	ft_free(vars->img_wall_east);
	mlx_destroy_image(vars->mlx, vars->img_wall_west->img);
	ft_free(vars->img_wall_west);
	ft_free(vars->ray->rayDir);
	ft_free(vars->ray->map);
	ft_free(vars->ray->deltaDist);
	ft_free(vars->ray->sideDist);
	ft_free(vars->ray->step);
	ft_free(vars->ray);
}

void	ft_free_all(t_prgrm *vars)
{
	int	i;

	i = 0;
	ft_free(vars->playa);
	ft_free(vars->dir);
	ft_free(vars->old_dir);
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
	if (vars->map_error == 0)
	{
		mlx_destroy_image(vars->mlx, vars->img->img);
		ft_free(vars->img);
		ft_free_all_2(vars);
	}
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
	if (vars->map_error == 0)
	{
		mlx_destroy_window(vars->mlx, vars->mlx_win);
		mlx_destroy_display(vars->mlx);
		ft_free(vars->mlx);
	}
	free (vars);
	exit(0);
	return (1);
}
