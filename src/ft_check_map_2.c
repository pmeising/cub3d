/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:26:53 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/06 18:51:11 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
* checks if the whole row (top/bottom) are closed;
*/
int	ft_check_top_bottom(char *str, int count)
{
	int	i;
	int	len;

	len = (int)ft_strlen(str);
	i = 0;
	while (i < len && str[i])
	{
		if (str[i] != '1' && str[i] != '2')
		{
			printf("Error: Map. Position %d:%d\n", i, count);
			return (1);
		}
		i++;
	}
	return (0);
}

/*
* checks first and last pos in map are valid;
*/
int	ft_check_first_last(char *str, int count)
{
	int	i;
	int	len;

	len = (int)ft_strlen(str);
	i = 0;
	while (i < len && str[i])
	{
		if (str[0] != '1' && str[0] != '2')
		{
			printf("Error. Map. Position %d:%d\n", count + 1, i);
			return (1);
		}
		if (str[len - 1] != '1' && str[len - 1] != '2')
		{
			printf("Error. Map. Position %d:%d\n", count + 1, len - 1);
			return (1);
		}
		i++;
	}
	return (0);
}

/*
*	direction: direction vector (wall pos. - playa pos.);
*	camera_vector: is calculated so that we have a perpendicular vector to the
*	direction vector. The length of the camera vector is 0.73% the length of the
*	direction vector, so that we can assure an angle of 66° FOV (i.e. Field of View) of the player.
*	Two vectors are perpendicular to one another, if the result of their multiplication is 0.
*	In our case, the direction vector always has one value set to 0.
*/
void	ft_init_vecs(t_prgrm *vars, char c)
{
	if (c == 'N')
	{
		vars->direction[0] = 0;
		vars->direction[1] = 1;
		vars->camera_vector[0] = 0.66;
		vars->camera_vector[1] = 0;
	}
	else if (c == 'S')
	{
		vars->direction[0] = 0;
		vars->direction[1] = -1;
		vars->camera_vector[0] = -0.66;
		vars->camera_vector[1] = 0;
	}
	else if (c == 'W')
	{
		vars->direction[0] = 1;
		vars->direction[1] = 0;
		vars->camera_vector[0] = 0;
		vars->camera_vector[1] = 0.66;

	}
	else if (c == 'E')
	{
		vars->direction[0] = -1;
		vars->direction[1] = 0;
		vars->camera_vector[0] = 0;
		vars->camera_vector[1] = -0.66;
	}
}
