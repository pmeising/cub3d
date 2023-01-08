/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:21:53 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/08 17:43:12 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
* W:119 ; A:97 ; S:115 ; D:100 
*/
int ft_movement(int keycode, t_prgrm *vars)
{
	if (keycode == 119)
	{
		printf("%d, %d\n", (int)(vars->playa[1]), (int)(vars->playa[0] + (vars->direction[0] * SPEED)));
		if (vars->map[(-1) * (int)(vars->playa[1])][(int)(vars->playa[0] + (vars->direction[0] * SPEED))] != '1')
			vars->playa[0] += vars->direction[0] * SPEED;
		if (vars->map[(-1) *(int)(vars->playa[1] + (vars->direction[1] * SPEED))][(int)(vars->playa[1])] != '1')
			vars->playa[1] += vars->direction[1] * SPEED;
	}
	else if (keycode == 97)
	{
		/*
		if (vars->map[(int)(vars->playa[1])][(int)(vars->playa[0]  - 1 * SPEED)] != '1')
			vars->playa[0] += vars->camera_vector[0] * SPEED;
		if (vars->map[(int)(vars->playa[1])][(int)(vars->playa[1] - 1 * SPEED)] != '1')
			vars->playa[1] += vars->camera_vector[1] * SPEED;
		*/
		double prev_dir_x = vars->direction[0];
		vars->direction[0] = vars->direction[0] * cos(SPEED) - vars->direction[1] * sin(SPEED);
		vars->direction[1] = prev_dir_x * sin(SPEED) + vars->direction[1] * cos(SPEED);
		double prev_cam_vec_x = vars->camera_vector[0];
		vars->camera_vector[0] = vars->camera_vector[0] * cos(SPEED) - vars->camera_vector[1] * sin(SPEED);
		vars->camera_vector[1] = prev_cam_vec_x * sin(SPEED) + vars->camera_vector[1] * cos(SPEED);
	}
	else if (keycode == 115)
	{
		
		// printf("%d, %d\n", (int)(vars->playa[1]), (int)(vars->playa[0] + ((vars->direction[0]) * SPEED)));
		if (vars->map[(-1) * (int)(vars->playa[1])][(int)(vars->playa[0] + ((vars->direction[0]) * SPEED))] != '1')
			vars->playa[0] += (vars->direction[0] * -1) * SPEED;
		if (vars->map[(-1) *(int)(vars->playa[1] + (vars->direction[1] * SPEED))][(int)(vars->playa[1])] != '1')
			vars->playa[1] += (vars->direction[1] * -1) * SPEED;
		
		// if (vars->map[(int)(vars->playa[0] - vars->direction[0] * SPEED)][(int)(vars->playa[1])] != '1')
		// 	vars->playa[0] -= vars->direction[0] * SPEED;
		// if (vars->map[(int)(vars->playa[1])][(int)(vars->playa[1] - vars->direction[1] * SPEED)] != '1')
		// 	vars->playa[1] -= vars->direction[1] * SPEED;
	}
	else if (keycode == 100)
	{
		/*	
		 if (vars->map[(int)(vars->playa[0] + 1 * SPEED)][(int)(vars->playa[1])] != '1')
			vars->playa[0] += vars->camera_vector[0] * SPEED;
		 if (vars->map[(int)(vars->playa[1])][(int)(vars->playa[1] + 1 * SPEED)] != '1')
			vars->playa[1] += vars->camera_vector[1] * SPEED;*/
		double prev_dir_x = vars->direction[0];
		vars->direction[0] = vars->direction[0] * cos(-SPEED) - vars->direction[1] * sin(-SPEED);
		vars->direction[1] = prev_dir_x * sin(-SPEED) + vars->direction[1] * cos(-SPEED);
		double prev_cam_vec_x = vars->camera_vector[0];
		vars->camera_vector[0] = vars->camera_vector[0] * cos(-SPEED) - vars->camera_vector[1] * sin(-SPEED);
		vars->camera_vector[1] = prev_cam_vec_x * sin(-SPEED) + vars->camera_vector[1] * cos(-SPEED);
	}
	ft_raycast(vars);
	return (keycode);
}