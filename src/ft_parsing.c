/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:30:28 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/24 09:48:26 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
* fill up the spaces in the beginning with -1;
* counts the total number of rows the map has;
*/
void	ft_read_map(t_prgrm *vars, char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		if (str[i] == ' ')
			str[i] = '2';
		i++;
	}
	if (str[i] == '\n')
		str[i] = '\0';
	if (i > vars->map_columns)
		vars->map_columns = i;
	vars->map[vars->map_rows] = ft_strdup(str);
	vars->map_rows++;
}

void	ft_parsing_4(t_prgrm *vars, char *str)
{
	char	*temp;
	int		i;
	int		len;

	i = 2;
	len = ft_strlen(str);
	if (ft_strnstr(str, "EA", len) != NULL)
	{
		temp = ft_strnstr(str, "EA", len);
		i = ft_skip_space(temp, i);
		vars->path_to_east = ft_strdup(&temp[i]);
		vars->path_to_east[(int)ft_strlen(vars->path_to_east) - 1] = '\0';
	}
	if (ft_strnstr(str, "F", len) != NULL)
	{
		temp = ft_strnstr(str, "F", len);
		i = ft_skip_space(temp, i);
		vars->floor_colour = ft_strdup(&temp[i]);
	}
	if (ft_strnstr(str, "C", len) != NULL)
	{
		temp = ft_strnstr(str, "C", len);
		i = ft_skip_space(temp, i);
		vars->ceiling_colour = ft_strdup(&temp[i]);
	}
}

void	ft_parsing_3(t_prgrm *vars, char *str)
{
	char	*temp;
	int		i;
	int		len;

	i = 2;
	len = ft_strlen(str);
	if (ft_strnstr(str, "SO", len) != NULL)
	{
		temp = ft_strnstr(str, "SO", len);
		i = ft_skip_space(temp, i);
		vars->path_to_south = ft_strdup(&temp[i]);
		vars->path_to_south[(int)ft_strlen(vars->path_to_south) - 1] = '\0';
	}
	else if (ft_strnstr(str, "WE", len) != NULL)
	{
		temp = ft_strnstr(str, "WE", len);
		i = ft_skip_space(temp, i);
		vars->path_to_west = ft_strdup(&temp[i]);
		vars->path_to_west[(int)ft_strlen(vars->path_to_west) - 1] = '\0';
	}
	else
		ft_parsing_4(vars, str);
}

/*
* return: 1 = error found line shouldnt start with \n;
* reads in the paths to the images for directions NOSW;
*/
int	ft_parsing_2(t_prgrm *vars, char *s)
{
	int		len;
	int		i;
	char	*temp;

	i = 2;
	len = ft_strlen(s);
	if (ft_strnstr(s, "NO", len) != NULL)
	{
		temp = ft_strnstr(s, "NO", len);
		i = ft_skip_space(temp, i);
		vars->path_to_north = ft_strdup(&temp[i]);
		vars->path_to_north[(int)ft_strlen(vars->path_to_north) - 1] = '\0';
	}
	if (ft_strnstr(s, "SO", len) || ft_strnstr(s, "WE", len) || \
		ft_strnstr(s, "EA", len) || ft_strnstr(s, "C", len) || \
		ft_strnstr(s, "F", len))
		ft_parsing_3(vars, s);
	else if (ft_strnstr(s, "1", len) != NULL)
		ft_read_map(vars, s);
	return (0);
}

void	ft_parsing(t_prgrm *vars)
{
	int		fd;
	char	*str;

	fd = open(vars->path_to_map, O_RDONLY, 0777);
	if (fd == -1)
	{
		vars->map_error = 2;
		perror("Error\nFile couldn't be opened");
		ft_close_program(vars);
	}
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
		{
			free(str);
			break ;
		}
		ft_parsing_2(vars, str);
		ft_free (str);
	}
	ft_buffer_map(vars);
	ft_mirror_map_2(vars);
	ft_path_exist(vars);
	ft_is_map_complete(vars);
}
