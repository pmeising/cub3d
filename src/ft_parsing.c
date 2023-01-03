/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:30:28 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/03 17:23:32 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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
		while ((j < dif) && temp[j])
		{
			temp[j] = '2';
			j++;
		}
		temp[j] = '\0';
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
		ft_printf("%s\n", vars->map[i]);
		i++;
	}
}

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

/*
* return: 1 = error found line shouldnt start with \n;
* reads in the paths to the images for directions NOSW;
*/
int	ft_helper1(t_prgrm *vars, char *str)
{ // NSOW may not always stand at first
	if (str[0] == '\n')
		return (0);
	if (str[0] == 'N' && str[1] == 'O')
		vars->path_to_north = ft_strdup(&str[3]);
	else if (str[0] == 'S' && str[1] == 'O')
		vars->path_to_south = ft_strdup(&str[3]);
	else if (str[0] == 'W' && str[1] == 'E')
		vars->path_to_west = ft_strdup(&str[3]);
	else if (str[0] == 'E' && str[1] == 'A')
		vars->path_to_east = ft_strdup(&str[3]);
	else if (str[0] == 'F')
		vars->floor_colour = ft_strdup(&str[2]);
	else if (str[0] == 'C')
		vars->ceiling_colour = ft_strdup(&str[2]);
	if ((ft_is_space(str[0]) == 1) || (ft_isdigit(str[0]) == 1))
		ft_read_map(vars, str);
	return (0);
}

void	ft_parsing(t_prgrm *vars)
{
	int		fd;
	char	*str;

	fd = open(vars->path_to_map, O_RDONLY, 0777);
	if (fd == -1)
		perror("File couldn't be opened.\n");
	while (1)
	{
		str = malloc(sizeof(char) * 2000);
		str = get_next_line(fd);
		if (str == NULL)
		{
			free(str);
			break ;
		}
		ft_helper1(vars, str);
		ft_free (str);
	}
	ft_buffer_map(vars);
	ft_is_map_complete(vars);
}
