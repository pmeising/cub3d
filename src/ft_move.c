/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:21:53 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/09 17:35:55 by pmeising         ###   ########.fr       */
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
		// printf("playa[1]: %d, playa[0] + (dir[0] * speed): %d\n", (int)(vars->playa[1]), (int)(vars->playa[0] + (vars->direction[0] * SPEED)));
		// printf("(-1) * (int)(vars->playa[1]): %d\n", (-1) * (int)(vars->playa[1]));
		printf("(int)(vars->playa[0] + (vars->direction[0] * SPEED)): %d\n", (int)(vars->playa[0] + (vars->direction[0] * SPEED)));
		if ((((-1) * (int)(vars->playa[1])) < (vars->map_rows)) && ((int)((vars->playa[0] + 0.5 )+ (vars->direction[0] * SPEED))) < vars->map_columns)
		{
			// printf("hi.\n"); //0
			/*
			* first check x coordinate then y coordinate for if we can walk there
			*/
			if (vars->map[(-1) * (int)(vars->playa[1])][(int)((vars->playa[0] + 0.5) + (vars->direction[0] * SPEED))] != '1')// &&
				// vars->map[(-1) * (int)(vars->playa[1])][(int)(vars->playa[0] + (vars->direction[0] * SPEED))] != 'N')
			{
				// printf("walking.\n");
				vars->playa[0] += vars->direction[0] * SPEED;
				// vars->playa[1] += vars->direction[1] * SPEED;
				printf("playa: %f:%f\n", vars->playa[0], vars->playa[1]);
			}
		}
		// printf("still going.\n");
		if ((((-1) *(int)(vars->playa[1] + (vars->direction[1] * SPEED + 0.5))) < vars->map_rows) && ((int)(vars->playa[1]) < vars->map_columns))
		{
			printf("(int)(vars->playa[1] + (vars->direction[1] * SPEED)): %d, (int)(vars->playa[0]): %d\n", (int)(vars->playa[1] + (vars->direction[1] * SPEED)), (int)(vars->playa[0]));
			if (vars->map[(-1) * (int)((vars->playa[1] + (vars->direction[1] * (double)SPEED) + 0.5))][(int)(vars->playa[0])] != '1')// && 
			// 	// vars->map[(-1) * (int)(vars->playa[1])][(int)(vars->playa[0] + (vars->direction[0] * SPEED))] != 'N')
			{
				printf("walking.\n");
				vars->playa[1] += vars->direction[1] * SPEED;
			}
		}
		// printf("playa after move: %f, %f\n", vars->playa[0], vars->playa[1]);
		// printf("Pos on map: %c\n", vars->map[(-1) *(int)vars->playa[1]][(int)vars->playa[0]]);
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
		if (vars->map[(-1) * (int)(vars->playa[1] + (vars->direction[1] * SPEED))][(int)(vars->playa[1])] != '1')
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