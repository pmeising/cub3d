/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 22:03:43 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/06 21:03:14 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
*	Interactions on the window can be caught and acted on.
*	Mask 17 represents the cross on the window, which triggers the closing
*	of the window and program.
*/
void	ft_hooks(t_prgrm *vars)
{
	mlx_hook(vars->mlx_win, 17, 0, ft_close_program, &vars);
}

/*
*	Each key is assigned its own keycode. By this we can identify user
*	actions.
*	Keys we need for this project:
*	W, A, S, D, 'right arrow key', 'left arrow key', ESC.
*	Bonus: Link the mouse movement to the adjustment of the POV
*/
int	ft_key_hook(int keycode, t_prgrm *vars)
{
	// int	i;

	// i = 1;
	printf("keycode: %d\n", keycode);
	if (keycode == 65307)
		ft_close_program(vars);
	// else if (keycode == 129 || keycode == 130)
	// {
	// 	if (keycode == 129)
	// 		i = -1;
	// 	ft_helper(vars, i);
	// 	// vars->old_direction[0] = vars->direction[0];
	// 	// vars->direction[0] = vars->direction[0] * cos(i * SPEED) - vars->direction[1] * sin(i * SPEED);
	// 	// vars->direction[1] = vars->old_direction[0] * sin(i * SPEED) - vars->direction[1] * cos(i * SPEED);
	// 	// vars->old_camera_vector[0] = vars->camera_vector[0];
	// 	// vars->camera_vector[0] = vars->camera_vector[0] * cos(i * SPEED) - vars->camera_vector[1] * sin(i * SPEED);
	// 	// vars->camera_vector[1] = vars->old_camera_vector[0] * sin(i * SPEED) + vars->camera_vector[1] * cos(i * SPEED);
	// 	// ft_raycast(vars);
	// }
	return (keycode);
}
