/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:15:36 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/10 21:45:49 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_init(t_prgrm *vars, char **argv, int argc)
{
	vars->argc = argc;
	vars->window_height = 540;
	vars->window_width = 960;
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
	vars->direction = malloc(sizeof(double) * 2);
	vars->direction[0] = 0;
	vars->direction[1] = 0;
	vars->old_direction = malloc(sizeof(double) * 2);
	vars->old_direction[0] = 0;
	vars->old_direction[1] = 0;
	vars->camera_vector = malloc(sizeof(double) * 2);
	vars->camera_vector[0] = 0;
	vars->camera_vector[1] = 0;
	vars->old_camera_vector = malloc(sizeof(double) * 2);
	vars->old_camera_vector[0] = 0;
	vars->old_camera_vector[1] = 0;
	vars->qubit = 0;
}

void	ft_check(t_prgrm *vars, void *con, int code)
{
	if (con == NULL && code == 1)
	{
		perror("Error\nConnection to graphics unit failed.\n");
		printf("Closing: %s\n", vars->path_to_map);
		exit(0);
	}
	else if (con == NULL && code == 2)
	{
		perror("Error\nCreation of window failed.\n");
		printf("Closing: %s\n", vars->path_to_map);
		exit(0);
	}
	else if (!con && code == 3)
	{
		perror("Malloc: ");
		exit(0);
	}	
}

// void	print_map(t_prgrm *vars)
// {
// 	int	i;

// 	i = 0;
// 	while (vars->map[i])
// 	{
// 		printf("%s", vars->map[i]);
// 		i++;
// 	}
// }

int	main(int argc, char	**argv)
{
	t_prgrm	*vars;

	vars = malloc(sizeof(t_prgrm));
	if (argc == 2)
	{
		ft_init(vars, argv, argc);
		ft_parsing(vars);
		vars->mlx = mlx_init();
		ft_check(vars, vars->mlx, 1);
		vars->mlx_win = mlx_new_window(vars->mlx, vars->window_width, vars->window_height, "cub3D");
		ft_check(vars, vars->mlx_win, 2);
		ft_raycasting(vars);
		ft_hooks(vars);
		mlx_key_hook(vars->mlx_win, ft_key_hook, vars);
		mlx_loop(vars->mlx);
		ft_close_program(vars);
	}
	write(1, "\n", 1);
	return (0);
}
