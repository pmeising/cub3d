/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb_conv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 16:28:33 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/13 14:13:49 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_unset(char **s_color_rgb)
{
	int	i;

	i = 0;
	while (s_color_rgb[i] && i < 3)
	{
		ft_free(s_color_rgb[i]);
		i++;
	}
	ft_free(s_color_rgb);
}

/*
* bitshift operation of the rgb values 
*/
unsigned int	ft_convert(int t, int r, int g, int b)
{
	return ((t & 0xff) << 24 | (r & 0xff) << 16 | (g & 0xff) << 8 | (b & 0xff));
}

/*
*	Takes a string i.e. "123,255,0"
*	Splits the string at ',' and converts the ints to 
*	their representation of hexadecimal in the form of the returned
*	Return value: unsigned int -> color of the corresponding area.
*/
unsigned int	ft_rgb_to_hex(char *color)
{
	int				color_rgb[3];
	int				i;
	char			**s_color_rgb;
	unsigned int	col;

	i = 0;
	s_color_rgb = ft_split(color, ',');
	while (s_color_rgb[i] && i < 3)
	{
		color_rgb[i] = ft_atoi(s_color_rgb[i]);
		if (color_rgb[i] < 0 || color_rgb[i] > 255)
		{
			printf("number is not a color\n");
			return (0);
		}
		i++;
	}
	col = ft_convert(0, color_rgb[0], color_rgb[1], color_rgb[2]);
	ft_unset(s_color_rgb);
	return (col);
}
