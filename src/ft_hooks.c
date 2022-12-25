/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 22:03:43 by pmeising          #+#    #+#             */
/*   Updated: 2022/12/25 22:41:33 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_hooks(t_prgrm *vars)
{
	mlx_hook(vars->mlx_win, 17, 0, ft_close_program, &vars);
}

int	ft_key_hook(int keycode, t_prgrm *vars)
{
	printf("keycode: %d\n", keycode);
	if (keycode == 65307)
		ft_close_program(vars);
	return (keycode);
}
