/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:15:36 by pmeising          #+#    #+#             */
/*   Updated: 2023/02/01 22:44:31 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_init_2(t_prgrm *vars)
{
	vars->old_cam_vec = malloc(sizeof(double) * 2);
	vars->old_cam_vec[0] = 0;
	vars->old_cam_vec[1] = 0;
	vars->qubit = 0;
	vars->map_error = 0;
}

void	ft_init(t_prgrm *vars, char **argv, int argc)
{
	vars->argc = argc;
	vars->window_height = HEIGHT;
	vars->window_width = WIDTH;
	vars->player_num = 0;
	vars->path_to_map = ft_strdup(argv[1]);
	vars->mlx = NULL;
	vars->mlx_win = NULL;
	vars->map = (char **)ft_calloc(sizeof(char *), 2001);
	vars->map[2000] = NULL;
	vars->map_rows = 0;
	vars->map_columns = 0;
	vars->playa = malloc(sizeof(double) * 2);
	vars->playa[0] = 0;
	vars->playa[1] = 0;
	vars->dir = malloc(sizeof(double) * 2);
	vars->dir[0] = 0;
	vars->dir[1] = 0;
	vars->old_dir = malloc(sizeof(double) * 2);
	vars->old_dir[0] = 0;
	vars->old_dir[1] = 0;
	vars->cam_vec = malloc(sizeof(double) * 2);
	vars->cam_vec[0] = 0;
	vars->cam_vec[1] = 0;
	ft_init_2(vars);
}

void	ft_check(t_prgrm *vars, void *con, int code)
{
	if (con == NULL && code == 1)
	{
		perror("Error\nConnection to graphics unit failed.\n");
		printf("Closing: %s\n", vars->path_to_map);
		ft_close_program(vars);
	}
	else if (con == NULL && code == 2)
	{
		perror("Error\nCreation of window failed.\n");
		printf("Closing: %s\n", vars->path_to_map);
		ft_close_program(vars);
	}
	else if (!con && code == 3)
	{
		perror("Error\nMalloc");
		ft_close_program(vars);
	}	
}

int	main(int argc, char	**argv)
{
	t_prgrm	*vars;

	if (argc == 2)
	{
		vars = malloc(sizeof(t_prgrm));
		ft_init(vars, argv, argc);
		ft_parsing(vars);
		vars->mlx = mlx_init();
		ft_check(vars, vars->mlx, 1);
		vars->mlx_win = mlx_new_window(vars->mlx, WIDTH, \
			HEIGHT, "cub3D");
		ft_check(vars, vars->mlx_win, 2);
		ft_raycasting(vars);
		ft_raycast(vars);
		ft_hooks(vars);
		mlx_key_hook(vars->mlx_win, ft_key_hook, vars);
		mlx_loop(vars->mlx);
		ft_close_program(vars);
	}
	else
		printf("Error\nWrong number of arguments\n");
	write(1, "\n", 1);
	return (0);
}
