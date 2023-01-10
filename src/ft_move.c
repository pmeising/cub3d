/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:21:53 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/10 21:44:36 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"



/*
* W:119 ; A:97 ; S:115 ; D:100
* first check x coordinate then y coordinate for if we can walk there 
*/
int ft_movement(int keycode, t_prgrm *vars)
{ // check x and y minimal/maximal wert !! first part w-e second part n-s
	if (keycode == 119)
	{
		// Move along the x achsis:
		printf("playa: %f:%f.\n would be: %f:%f\nIcon: %c\n", vars->playa[0], vars->playa[1], vars->playa[0] + vars->direction[0] * SPEED, vars->playa[1] + vars->direction[1] * SPEED, vars->map[-1 * (int)(vars->playa[1])][(int)vars->playa[0]]);
		if (vars->direction[0] > 0)
		{
			if (vars->map[-1 * (int)vars->playa[1]][(int)(vars->playa[0] + (vars->direction[0] * SPEED))] == '0')
				vars->playa[0] = vars->playa[0] + (vars->direction[0] * SPEED);
		}
		else if (vars->direction[0] < 0)
		{
			if ((int)(vars->playa[0] + (vars->direction[0] * SPEED)) > 0)
			{
				if (vars->map[-1 * (int)vars->playa[1]][(int)(vars->playa[0] + (vars->direction[0] * SPEED))] == '0')
					vars->playa[0] = vars->playa[0] + (vars->direction[0] * SPEED);	
			}
			else
				if (vars->map[-1 * (int)vars->playa[1]][(int)(vars->playa[0] + (vars->direction[0] * SPEED))] == '0')
					vars->playa[0] = vars->playa[0] + (vars->direction[0] * SPEED);
		}
		// Move along the y achsis:
		if (vars->direction[1] < 0)
		{
			if (vars->map[(int)(1.25 + -1 * (vars->playa[1] + (vars->direction[1] * SPEED)))][(int)vars->playa[0]] == '0')
				vars->playa[1] = vars->playa[1] + (vars->direction[1] * SPEED);
		}
		else if (vars->direction[1] > 0)
		{
			if (vars->map[(int)(-1 * (vars->playa[1] + (vars->direction[1] * SPEED)))][(int)vars->playa[0]] == '0')
				vars->playa[1] = vars->playa[1] + (vars->direction[1] * SPEED);
		}
	}
	else if (keycode == 115)
	{
		// Move along the x achsis:
		if (-vars->direction[0] > 0)
		{
			if (vars->map[-1 * (int)vars->playa[1]][1 + (int)(vars->playa[0] + (-vars->direction[0] * SPEED))] == '0')
				vars->playa[0] = vars->playa[0] + (-vars->direction[0] * SPEED);
		}
		else if (-vars->direction[0] < 0)
		{
			if ((int)(vars->playa[0] + (-vars->direction[0] * SPEED)) > 0)
			{
				if (vars->map[-1 * (int)vars->playa[1]][-1 + (int)(vars->playa[0] + (-vars->direction[0] * SPEED))] == '0')
					vars->playa[0] = vars->playa[0] + (-vars->direction[0] * SPEED);	
			}
			else
				if (vars->map[-1 * (int)vars->playa[1]][(int)(vars->playa[0] + (-vars->direction[0] * SPEED))] == '0')
					vars->playa[0] = vars->playa[0] + (-vars->direction[0] * SPEED);
		}
		// Move along the y achsis:
		if (-vars->direction[1] < 0)
		{
			if (vars->map[2 + (int)(-1 * (vars->playa[1] + (-vars->direction[1] * SPEED)))][(int)vars->playa[0]] == '0')
				vars->playa[1] = vars->playa[1] + (-vars->direction[1] * SPEED);
		}
		else if (vars->direction[1] > 0)
		{
			if (vars->map[(int)(-1 * (vars->playa[1] + (-vars->direction[1] * SPEED)))][(int)vars->playa[0]] == '0')
				vars->playa[1] = vars->playa[1] + (-vars->direction[1] * SPEED);
		}
	}
	else if (keycode == 97)
	{
		double prev_dir_x = vars->direction[0];
		vars->direction[0] = vars->direction[0] * cos(SPEED) - vars->direction[1] * sin(SPEED);
		vars->direction[1] = prev_dir_x * sin(SPEED) + vars->direction[1] * cos(SPEED);
		double prev_cam_vec_x = vars->camera_vector[0];
		vars->camera_vector[0] = vars->camera_vector[0] * cos(SPEED) - vars->camera_vector[1] * sin(SPEED);
		vars->camera_vector[1] = prev_cam_vec_x * sin(SPEED) + vars->camera_vector[1] * cos(SPEED);
	}
	else if (keycode == 100)
	{
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