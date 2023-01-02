/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 19:15:36 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/02 20:00:51 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_init(t_prgrm *vars, char **argv, int argc)
{
	vars->argc = argc;
	printf("%d\n", vars->argc);
	vars->path_to_map = ft_strdup(argv[1]);
	vars->mlx = NULL;
	vars->mlx_win = NULL;
	// vars->map = malloc(sizeof(char *) * 2001);
	vars->map = (char **)ft_calloc(sizeof(char *), 2001);
	vars->map[2000] = NULL;
	vars->map_rows = 0;
	printf("%s\n", vars->path_to_map);
}

void ft_free_all(t_prgrm *vars)
{
	ft_free(vars->path_to_south);
	ft_free(vars->path_to_north);
	ft_free(vars->path_to_east);
	ft_free(vars->path_to_west);
	ft_free(vars->floor_colour);
	ft_free(vars->ceiling_colour);
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
	free (vars);
	exit(0);
	return (1);
}

void	ft_check(t_prgrm *vars, void *con, int code)
{
	if (con == NULL && code == 1)
	{
		perror("Error\nConnection to graphics unit failed.\n");
		printf("Closing: %s\n", vars->path_to_map);
		// ft_close_program(&vars);
	}
	else if (con == NULL && code == 2)
	{
		perror("Error\nCreation of window failed.\n");
		printf("Closing: %s\n", vars->path_to_map);
		// ft_close_program(&vars);
	}
}

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
		vars->mlx_win = mlx_new_window(vars->mlx, 960, 540, "cub3D");
		ft_check(vars, vars->mlx_win, 2);
		// ft_operate(vars);
		ft_hooks(vars);
		mlx_key_hook(vars->mlx_win, ft_key_hook, vars);
		mlx_loop(vars->mlx);
		ft_close_program(vars);
	}
	write(1, "\n", 1);
	return (0);
}
