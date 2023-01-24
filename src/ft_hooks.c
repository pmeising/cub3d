/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 22:03:43 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/24 09:49:55 by pmeising         ###   ########.fr       */
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
	mlx_hook(vars->mlx_win, 17, 0, ft_close_program_2, vars);
}

/*d
*	Each key is assigned its own keycode. By this we can identify user
*	actions.
*	Keys we need for this project:
*	W, A, S, D, 'right arrow key', 'left arrow key', ESC.
*	Bonus: Link the mouse movement to the adjustment of the POV
*	65361/65363: left/right;
*/
int	ft_key_hook(int keycode, t_prgrm *vars)
{
	int	i;
	int	keykot;

	keykot = 0;
	i = 1;
	if (keycode == 65307)
		ft_close_program(vars);
	else if (keycode == 65361 || keycode == 65363)
	{
		if (keycode == 65363)
			i = -1;
		ft_helper_rotate(vars, i);
	}
	keykot = ft_movement(keycode, vars);
	return (keykot);
}
