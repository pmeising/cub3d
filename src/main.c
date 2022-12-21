/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:15:36 by pmeising          #+#    #+#             */
/*   Updated: 2022/12/21 22:06:39 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_exit_program(t_prgrm vars)
{
	printf("Error: %s\n", vars.path_to_map);
	printf("Exiting program.\n");
}

void	ft_mlx_funcs(t_prgrm vars)
{
	printf("hi.\n");
	vars.mlx_win = mlx_new_window(vars.mlx, 1920, 1080, "cub3D");
	// printf("there.\n");
	if (vars.mlx_win == NULL)
	{
		perror("Error\nCreating new window failed.\n");
		ft_exit_program(vars);
	}
	// printf("going.\n");
	mlx_loop(vars.mlx);
}

void	ft_init(t_prgrm vars, char **argv, int argc)
{
	vars.argc = argc;
	vars.path_to_map = ft_strdup(argv[1]);
	vars.mlx = NULL;
	vars.mlx_win = NULL;
	printf("%s\n", vars.path_to_map);
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
	mlx_destroy_window(vars->mlx, vars->mlx_win);
	mlx_destroy_display(vars->mlx);
	ft_free(vars->path_to_map);
	ft_free(vars->mlx_win);
	return (1);
}

void	ft_check(t_prgrm vars, void *con, int code)
{
	if (con == NULL && code == 1)
	{
		perror("Error\nConnection to graphics unit failed.\n");
		ft_close_program(&vars);
	}
	else if (con == NULL && code == 2)
	{
		perror("Error\nCreation of window failed.\n");
		ft_close_program(&vars);
	}
}

void	ft_hooks(t_prgrm vars)
{
	mlx_hook(vars.mlx_win, 17, 0, ft_close_program, &vars);
}

int	main(int argc, char	**argv)
{
	t_prgrm	vars;

	printf("%s\n", argv[1]);
	if (argc == 2)
	{
		ft_init(vars, argv, argc);
		vars.mlx = mlx_init();
		ft_check(vars, vars.mlx, 1);
		// ft_put_values(&vars);
		// ft_read_from_map(&vars, argv[1]);
		// ft_check_map_border(&vars);
		vars.mlx_win = mlx_new_window(vars.mlx, 960, 540, "cub3D");
		ft_check(vars, vars.mlx_win, 2);
		// ft_create_image(&vars);
		ft_hooks(vars);
		// mlx_key_hook(vars.mlx_win, ft_key_hook, &vars);
		mlx_loop(vars.mlx);
	}
	ft_close_program(&vars);
	return (0);
}