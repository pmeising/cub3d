/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_map_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:26:53 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/04 11:02:30 by pmeising         ###   ########.fr       */
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
