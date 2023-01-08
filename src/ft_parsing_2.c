/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:30:28 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/08 12:31:39 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_buffer_helper(int dif, t_prgrm *vars, int i)
{
	char	*temp;
	char	*temp_2;
	int		j;

	dif = vars->map_columns - (int)ft_strlen(vars->map[i]);
	if (dif > 0)
	{
		j = 0;
		temp = malloc(sizeof(char) * dif);
		while (j < dif)
		{
			temp[j] = '2';
			j++;
		}
		temp[j - 1] = '\0';
		temp_2 = ft_strjoin(vars->map[i], temp);
		ft_free(vars->map[i]);
		ft_free(temp);
		vars->map[i] = ft_strdup(temp_2);
		ft_free(temp_2);
	}
}

/*
* fill up overhang of rows shorter than the longest row
* fill up with 2's;
*/
void	ft_buffer_map(t_prgrm *vars)
{
	int		i;
	int		dif;

	i = 0;
	dif = 0;
	while (i < vars->map_rows)
	{
		ft_buffer_helper(dif, vars, i);
		i++;
	}
}
