/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:21:53 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/24 10:18:52 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_open_door(t_prgrm *vars)
{
	if (vars->map[(int)(vars->playa[1] + vars->dir[1] * (double)SPEED)] \
		[(int)(vars->playa[0] + vars->dir[0] * (double)SPEED)] == 'D')
	{
		vars->map[(int)(vars->playa[1] + vars->dir[1] * (double)SPEED)] \
		[(int)(vars->playa[0] + vars->dir[0] * (double)SPEED)] = 'O';
		vars->map[(int)(vars->playa[1] + vars->dir[1] * (double)SPEED)] \
		[1 + (int)(vars->playa[0] + vars->dir[0] * (double)SPEED)] = 'd';
	}
	else if (vars->map[(int)(vars->playa[1] + vars->dir[1] * (double)SPEED)] \
	[(int)(vars->playa[0] + vars->dir[0] * (double)SPEED)] == 'd')
	{
		vars->map[(int)(vars->playa[1] + vars->dir[1] * (double)SPEED)] \
		[(int)(vars->playa[0] + vars->dir[0] * (double)SPEED)] = '1';
		vars->map[(int)(vars->playa[1] + vars->dir[1] * (double)SPEED)] \
		[-1 + (int)(vars->playa[0] + vars->dir[0] * (double)SPEED)] = 'D';
	}
}
