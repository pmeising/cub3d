/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:21:53 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/12 16:17:08 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// void	ft_move_smooth(t_prgrm *vars, int dir)
// {
// 	double	smooth;

// 	smooth = 0.2;
// 	while (smooth <= 1)
// 	{
// 		vars->playa[dir] = vars->playa[dir] + (vars->direction[dir] * (double)(SPEED * smooth));
// 		ft_raycast(vars);
// 		usleep(1000);
// 		smooth = smooth + 0.2;
// 	}
// }

/*
* W:119 ; A:97 ; S:115 ; D:100
* first check x coordinate then y coordinate for if we can walk there 
*/
int ft_movement(int keycode, t_prgrm *vars)
{ // check x and y minimal/maximal wert !! first part w-e second part n-s
	// printf("before: playa: %f:%f.\n would be: %f:%f\nIcon: %c\n", vars->playa[0], vars->playa[1], vars->playa[0] + vars->direction[0] * SPEED, vars->playa[1] + vars->direction[1] * SPEED, vars->map[(int)(vars->playa[1])][(int)vars->playa[0]]);
	if (keycode == 119)// W
	{
		if (vars->direction[0] > 0) // EAST
		{
			if (vars->map[(int)vars->playa[1]][(int)(vars->playa[0] + (vars->direction[0] * (double)SPEED))] == '0' || vars->map[(int)vars->playa[1]][(int)(vars->playa[0] + (vars->direction[0] * (double)SPEED))] == 'O') // O not 0 O stands for 'Open door'
				vars->playa[0] = vars->playa[0] + (vars->direction[0] * (double)SPEED);
		}
		else if (vars->direction[0] < 0) // WEST
		{
			if ((int)(vars->playa[0] + (vars->direction[0] * (double)SPEED)) > 0)
			{
				if (vars->map[(int)vars->playa[1]][(int)(vars->playa[0] + (vars->direction[0] * (double)SPEED))] == '0' || vars->map[(int)vars->playa[1]][(int)(vars->playa[0] + (vars->direction[0] * (double)SPEED))] == 'O')
					vars->playa[0] = vars->playa[0] + (vars->direction[0] * (double)SPEED);	
			}
			else
				if (vars->map[(int)vars->playa[1]][(int)(vars->playa[0] + (vars->direction[0] * (double)SPEED))] == '0' || vars->map[(int)vars->playa[1]][(int)(vars->playa[0] + (vars->direction[0] * (double)SPEED))] == 'O')
					vars->playa[0] = vars->playa[0] + (vars->direction[0] * (double)SPEED);
		}
		// Move along the y achsis:
		if (vars->direction[1] < 0)
		{
			if (vars->map[(int)((vars->playa[1] + (vars->direction[1] * SPEED)))][(int)vars->playa[0]] == '0' || vars->map[(int)((vars->playa[1] + (vars->direction[1] * SPEED)))][(int)vars->playa[0]] == 'O')
				vars->playa[1] = vars->playa[1] + (vars->direction[1] * SPEED);
		}
		else if (vars->direction[1] > 0)
		{
			if (vars->map[(int)((vars->playa[1] + (vars->direction[1] * SPEED)))][(int)vars->playa[0]] == '0' || vars->map[(int)((vars->playa[1] + (vars->direction[1] * SPEED)))][(int)vars->playa[0]] == 'O')
				vars->playa[1] = vars->playa[1] + (vars->direction[1] * SPEED);
		}
	}
	else if (keycode == 115)
	{
		if (-vars->direction[0] > 0) // EAST
		{
			if (vars->map[(int)vars->playa[1]][(int)(vars->playa[0] + (-vars->direction[0] * (double)SPEED))] == '0' || vars->map[(int)vars->playa[1]][(int)(vars->playa[0] + (-vars->direction[0] * (double)SPEED))] == 'O')
				vars->playa[0] = vars->playa[0] + (-vars->direction[0] * (double)SPEED);
		}
		else if (-vars->direction[0] < 0) // WEST
		{
			if ((int)(vars->playa[0] + (-vars->direction[0] * (double)SPEED)) > 0)
			{
				if (vars->map[(int)vars->playa[1]][(int)(vars->playa[0] + (-vars->direction[0] * (double)SPEED))] == '0' || vars->map[(int)vars->playa[1]][(int)(vars->playa[0] + (-vars->direction[0] * (double)SPEED))] == 'O')
					vars->playa[0] = vars->playa[0] + (-vars->direction[0] * (double)SPEED);	
			}
			else
				if (vars->map[(int)vars->playa[1]][(int)(vars->playa[0] + (-vars->direction[0] * (double)SPEED))] == '0' || vars->map[(int)vars->playa[1]][(int)(vars->playa[0] + (-vars->direction[0] * (double)SPEED))] == 'O')
					vars->playa[0] = vars->playa[0] + (-vars->direction[0] * (double)SPEED);
		}
		// Move along the y achsis:
		if (-vars->direction[1] < 0)
		{
			if (vars->map[(int)((vars->playa[1] + (-vars->direction[1] * SPEED)))][(int)vars->playa[0]] == '0' || vars->map[(int)((vars->playa[1] + (-vars->direction[1] * SPEED)))][(int)vars->playa[0]] == 'O')
				vars->playa[1] = vars->playa[1] + (-vars->direction[1] * SPEED);
		}
		else if (-vars->direction[1] > 0)
		{
			if (vars->map[(int)((vars->playa[1] + (-vars->direction[1] * SPEED)))][(int)vars->playa[0]] == '0' || vars->map[(int)((vars->playa[1] + (-vars->direction[1] * SPEED)))][(int)vars->playa[0]] == 'O')
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
	else if (keycode == 32) // SPACEBAR
	{
		if (vars->map[(int)(vars->playa[1] + vars->direction[1] * (double)SPEED)][(int)(vars->playa[0] + vars->direction[0] * (double)SPEED)] == 'D')
		{
			vars->map[(int)(vars->playa[1] + vars->direction[1] * (double)SPEED)][(int)(vars->playa[0] + vars->direction[0] * (double)SPEED)] = 'O';
			vars->map[(int)(vars->playa[1] + vars->direction[1] * (double)SPEED)][1 + (int)(vars->playa[0] + vars->direction[0] * (double)SPEED)] = 'd';
			printf("Opened door.\n");
		}
		else if (vars->map[(int)(vars->playa[1] + vars->direction[1] * (double)SPEED)][(int)(vars->playa[0] + vars->direction[0] * (double)SPEED)] == 'd')
		{
			vars->map[(int)(vars->playa[1] + vars->direction[1] * (double)SPEED)][(int)(vars->playa[0] + vars->direction[0] * (double)SPEED)] = '1';
			vars->map[(int)(vars->playa[1] + vars->direction[1] * (double)SPEED)][-1 + (int)(vars->playa[0] + vars->direction[0] * (double)SPEED)] = 'D';
			printf("Closed door.\n");
		}
	}
	ft_raycast(vars);
	return (keycode);
}