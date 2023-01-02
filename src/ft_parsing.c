/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:30:28 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/02 20:42:43 by pmeising         ###   ########.fr       */
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

/*
* fill up overhang of rows shorter than the longest row
* fill up with -1;
*/
void	ft_buffer_map(t_prgrm *vars)
{
	int		i;
	int		j;
	int		dif;
	char	*temp;
	char	*temp_2;

	i = 0;
	while (i < vars->map_rows)
	{
		dif = vars->map_columns - (int)ft_strlen(vars->map[i]);
		if (dif > 0)
		{
			j = 0;
			temp = malloc(sizeof(char) * dif);
			while (temp[j] && j < dif)
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
		ft_printf("%s\n", vars->map[i]);
		i++;
	}
}

/*
* return: 1 = error found line shouldnt start with \n;
*/
int	ft_helper1(t_prgrm *vars, char *str)
{
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

/*
* checks if the whole row (top/bottom) are closed;
*/
int ft_check_all_1(char *str)
{
	int i;

	i = 0;
	while (i < (int)ft_strlen(str) && str[i] && str[i] != '\n') 
	{
		if (str[i] != '1' && str[i] != '2')
		{
			printf("error: map not closed\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int ft_check_first_pos(char *str)
{
	if (str[0] != '1' && str[0] != '2')
	{
		printf("first pos not closed\n");
		return (1);
	}
	return (0);
}

int ft_check_last_pos(char *str)
{
	int line_len;
	line_len = (int)ft_strlen(str);
	
	if (str[line_len - 1] != '1' && str[line_len - 1] != '2')
	{
		//printf("pos:%c:", str[line_len - 1]);
		printf("last pos not closed\n");
		return (1);
	}
	return (0);
}

int ft_check_overhang(char *str, t_prgrm *vars, int num_row)
{
	int len = ft_strlen(str);

	if (len < vars->map_columns)
	{
		while (str[len])
		{
			if (str[len] != '1' && str[len] != '2')
			{
				printf("overhang of line %d not close\n", num_row);
				return (1);
			}
			len++;
		}
	}
	return (0);
}

int ft_check_middle(char *str)
{
	int i;
	i = 0;
	
	while (str[i] && i < (int)ft_strlen(str))
	{
		if (i > 0)
		{
			if (str[i] == '2' && (str[i - 1] != '1' && str[i - 1] != '2'))
			{
				printf("map not closed in the middle\n");
				return(1);
			}
			else if (str[i] == '2' && (str[i + 1] != '1' && str[i + 1] != '2' && str[i + 1] != '\0'))
			{
				printf("map not closed in the middle\n");
				return(1);
			}
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
	int count;
	char *cur_line;

	count = 0;
	while (count < vars->map_rows)
	{
		cur_line = vars->map[count];
		if (count == 0 || count == vars->map_rows)
		{
				if (ft_check_all_1(cur_line) == 1)
					return (1);
		}
		else
		{
			if (ft_check_first_pos(cur_line) == 1)
				return(1);
			if (ft_check_last_pos(cur_line) == 1)
				return (1);
			if (ft_check_overhang(cur_line, vars, count) == 1)
				return (1);
			if (ft_check_middle(cur_line) == 1)
				return (1);
		}
		count++;
	}
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
			if (vars->map[i][j] == 'N' || vars->map[i][j] == 'S' || vars->map[i][j] == 'E' || vars->map[i][j] == 'W')
				playa++;
			else if (vars->map[i][j] != '0' && vars->map[i][j] != '1' && vars->map[i][j] != '2')
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
			free (str);
			break;
		}
		ft_helper1(vars, str);
		ft_free (str);
	}
	ft_buffer_map(vars);
	ft_is_map_complete(vars);
}
