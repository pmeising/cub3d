/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_funcs_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:46:50 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/16 15:53:51 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_free(void *cont)
{
	if (cont)
	{
		free (cont);
		cont = NULL;
	}
}

void	ft_helper_local(t_prgrm *vars)
{
	ft_free(vars->playa);
	ft_free(vars->dir);
	ft_free(vars->old_dir);
	ft_free(vars->camera_vector);
	ft_free(vars->old_camera_vector);
	ft_free(vars->path_to_map);
	ft_free(vars->path_to_north);
	ft_free(vars->path_to_south);
}

int	ft_close_program_2(t_prgrm *vars)
{
	int	i;

	i = 0;
	ft_helper_local(vars);
	while (vars->map[i] != NULL)
	{
		ft_free (vars->map[i]);
		i++;
	}
	ft_free(vars->map);
	mlx_destroy_image(vars->mlx, vars->img->img);
	ft_free(vars->img);
	ft_free_all_2(vars);
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	mlx_destroy_display(vars->mlx);
	ft_free(vars->mlx);
	ft_free(vars);
	exit(0);
	return (0);
}
