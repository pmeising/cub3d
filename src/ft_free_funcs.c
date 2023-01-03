/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:24:59 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/03 17:18:24 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_free_all(t_prgrm *vars)
{
	int	i;

	i = 0;
	ft_free(vars->path_to_south);
	ft_free(vars->path_to_north);
	ft_free(vars->path_to_east);
	ft_free(vars->path_to_west);
	ft_free(vars->floor_colour);
	ft_free(vars->ceiling_colour);
	while (vars->map[i] != NULL)
	{
		ft_free (vars->map[i]);
		i++;
	}
	ft_free(vars->map);
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
	free (vars);
	exit(0);
	return (1);
}
