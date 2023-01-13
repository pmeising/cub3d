/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:26:53 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/13 14:18:04 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_check_map_closed(t_prgrm *vars)
{
	int	i;
	int	j;

	i = 1;
	while (vars->map[i])
	{
		j = 1;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == '0')
			{
				if (vars->map[i + 1][j] == '2' || vars->map[i - 1][j] == '2' \
					|| vars->map[i][j + 1] == '2' || vars->map[i][j - 1] == '2')
				{
					printf("Unclosed walls at position %d:%d.\n", i + 1, j);
					return (1);
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

/*
* check if map is enclosed by walls;
*/
int	ft_is_closed(t_prgrm *vars)
{
	int		count;
	char	*cur_line;

	count = 0;
	while (count < vars->map_rows)
	{
		cur_line = vars->map[count];
		if (count == 0 || (count + 1) == vars->map_rows)
		{
			if (ft_check_top_bottom(cur_line, count) == 1)
				return (1);
		}
		else
		{
			if (ft_check_first_last(cur_line, count) == 1)
				return (1);
		}
		count++;
	}
	if (ft_check_map_closed(vars) == 1)
		return (1);
	printf("map is closed.\n");
	return (0);
}

int	ft_has_playa_2(t_prgrm *vars, char c, int y, int x)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		vars->playa[0] = (double)x - (double)0.5;
		vars->playa[1] = (double)(y) + (double)0.5;
		ft_init_vecs(vars, c);
		vars->map[y][x] = '0';
		printf("playa: x:%f, y:%f\n", vars->playa[0], vars->playa[1]);
		vars->player_num++;
	}
	else if (c != '0' && c != '1' && c != '2' && c != 'D')
	{
		printf("Unidentified object found at: x:%d:y:%d\n", x, y);
		return (1);
	}
	return (0);
}

int	ft_has_playa(t_prgrm *vars)
{
	int	x;
	int	y;

	y = 0;
	while (vars->map[y] != NULL)
	{
		x = 0;
		while (vars->map[y][x] != '\0')
		{
			if (ft_has_playa_2(vars, vars->map[y][x], y, x) == 1)
				return (1);
			x++;
		}
		y++;
	}
	printf("player # : %d\n", vars->player_num);
	if (vars->player_num != 1)
	{
		printf("\nA DOUBLE AGENT IS TRYING TO OVERTAKE YOU, ABORT MISSION.... \
			I REPEAT, ABORT MISSION!!!\n");
		return (1);
	}
	return (0);
}

void	ft_is_map_complete(t_prgrm *vars)
{
	if (ft_has_playa(vars) == 1)
		exit(EXIT_FAILURE);
	if (ft_is_closed(vars) == 1)
	{
		printf("Map invalid, unclosed walls.\n");
		exit(EXIT_FAILURE);
	}
}
