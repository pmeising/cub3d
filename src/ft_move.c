/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:21:53 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/24 10:12:15 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_movement_w(t_prgrm *vars)
{
	if (vars->map[(int)vars->playa[1]][(int)(vars->playa[0] + (vars->dir[0] \
		* (double)SPEED))] == '0' || vars->map[(int)vars->playa[1]][\
		(int)(vars->playa[0] + (vars->dir[0] * (double)SPEED))] == 'O')
		vars->playa[0] = vars->playa[0] + (vars->dir[0] * (double)SPEED);
	if (vars->map[(int)((vars->playa[1] + (vars->dir[1] * SPEED)))][\
		(int)vars->playa[0]] == '0' || vars->map[(int)((vars->playa[1] + \
		(vars->dir[1] * SPEED)))][(int)vars->playa[0]] == 'O')
			vars->playa[1] = vars->playa[1] + (vars->dir[1] * SPEED);
}

void	ft_movement_s(t_prgrm *vars)
{
	if (vars->map[(int)vars->playa[1]][(int)(vars->playa[0] + (-vars->dir[0] \
		* (double)SPEED))] == '0' || vars->map[(int)vars->playa[1]][\
		(int)(vars->playa[0] + (-vars->dir[0] * (double)SPEED))] == 'O')
		vars->playa[0] = vars->playa[0] + (-vars->dir[0] * (double)SPEED);
	if (vars->map[(int)((vars->playa[1] + (-vars->dir[1] * SPEED)))][\
		(int)vars->playa[0]] == '0' || vars->map[(int)((vars->playa[1] + \
		(-vars->dir[1] * SPEED)))][(int)vars->playa[0]] == 'O')
			vars->playa[1] = vars->playa[1] + (-vars->dir[1] * SPEED);
}

void	ft_movement_d(t_prgrm *vars)
{
	if (vars->map[(int)vars->playa[1]][(int)(vars->playa[0] + (vars->camera_vector[0] \
		* (double)SPEED))] == '0')
		vars->playa[0] = vars->playa[0] + (vars->camera_vector[0] * (double)SPEED);
	if (vars->map[(int)((vars->playa[1] + (vars->camera_vector[1] * (double)SPEED)))][\
		(int)vars->playa[0]] == '0')
			vars->playa[1] = vars->playa[1] + (vars->camera_vector[1] * SPEED);
}

void	ft_movement_a(t_prgrm *vars)
{
	if (vars->map[(int)vars->playa[1]][(int)(vars->playa[0] + (-vars->camera_vector[0] \
		* (double)SPEED))] == '0')
		vars->playa[0] = vars->playa[0] + (-vars->camera_vector[0] * (double)SPEED);
	if (vars->map[(int)((vars->playa[1] + (-vars->camera_vector[1] * (double)SPEED)))][\
		(int)vars->playa[0]] == '0')
			vars->playa[1] = vars->playa[1] + (-vars->camera_vector[1] * (double)SPEED);
}

/*
*	enables rotation of the field of view (i.e. FOV) using the keys
*	'A' and 'D'
*/
void	ft_rotate_fov(t_prgrm *vars, int dir)
{
	double	prev_dir_x;
	double	prev_cam_vec_x;

	prev_dir_x = vars->dir[0];
	prev_cam_vec_x = vars->camera_vector[0];
	vars->dir[0] = vars->dir[0] * cos(dir * SPEED) - vars->dir[1] * \
	sin(dir * SPEED);
	vars->dir[1] = prev_dir_x * sin(dir * SPEED) + vars->dir[1] * \
	cos(dir * SPEED);
	vars->camera_vector[0] = vars->camera_vector[0] * cos(dir * SPEED) \
	- vars->camera_vector[1] * sin(dir * SPEED);
	vars->camera_vector[1] = prev_cam_vec_x * sin(dir * SPEED) \
	+ vars->camera_vector[1] * cos(dir * SPEED);
}

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

/*
* W:119 ; A:97 ; S:115 ; D:100; Spacebar:32
* first check x coordinate then y coordinate for if we can walk there 
* 'O' not '0'. 'O' stands for 'Open door'
*/
int	ft_movement(int keycode, t_prgrm *vars)
{
	if (keycode == 119)
		ft_movement_w(vars);
	else if (keycode == 115)
		ft_movement_s(vars);
	else if (keycode == 97)
		ft_movement_a(vars);
		// ft_rotate_fov(vars, 1);
	else if (keycode == 100)
		ft_movement_d(vars);
		// ft_rotate_fov(vars, -1);
	else if (keycode == 32)
		ft_open_door(vars);
	ft_raycast(vars);
	return (keycode);
}
