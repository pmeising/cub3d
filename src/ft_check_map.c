/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:26:53 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/03 17:46:07 by pmeising         ###   ########.fr       */
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
			printf("Error: Map. Position %d:%d\n", count + 1, i);
			return (1);
		}
		i++;
	}
	return (0);
}

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
					printf("Unclosed walls at position %d:%d.\n", j + 1, i + 1);
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

int	ft_has_playa(t_prgrm *vars)
{
	int	i;
	int	j;
	int	playa;

	i = 0;
	playa = 0;
	while (vars->map[i] != NULL)
	{
		j = 0;
		while (vars->map[i][j] != '\0')
		{
			if (vars->map[i][j] == 'N' || vars->map[i][j] == 'S' \
				|| vars->map[i][j] == 'E' || vars->map[i][j] == 'W')
			{
				vars->playa[0] = j + 1;
				vars->playa[1] = i + 1;
				printf("playa: %d, %d\n", vars->playa[0], vars->playa[1]);
				playa++;
			}
			else if (vars->map[i][j] != '0' && vars->map[i][j] != '1' \
				&& vars->map[i][j] != '2')
			{
				printf("Unidentified object found: '%c'\n", vars->map[i][j]);
				return (1);
			}
			j++;
		}
		i++;
	}
	if (playa != 1)
	{
		printf("\nA DOUBLE AGENT IS TRYING TO OVERTAKE YOU, ABORT MISSION.... I REPEAT, ABORT MISSION!!!\n");
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