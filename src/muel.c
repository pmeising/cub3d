/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   muel.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 10:59:50 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/04 11:00:38 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// int ft_check_last_pos(char *str)
// {
// 	int line_len;
// 	line_len = (int)ft_strlen(str);

// 	if (str[line_len - 1] != '1' && str[line_len - 1] != '2')
// 	{
// 		//printf("pos:%c:", str[line_len - 1]);
// 		printf("last pos not closed\n");
// 		return (1);
// 	}
// 	return (0);
// }

// int ft_check_overhang(char *str, t_prgrm *vars, int num_row)
// {
// 	int len = ft_strlen(str);

// 	if (len < vars->map_columns)
// 	{
// 		while (str[len])
// 		{
// 			if (str[len] != '1' && str[len] != '2')
// 			{
// 				printf("overhang of line %d not close\n", num_row);
// 				return (1);
// 			}
// 			len++;
// 		}
// 	}
// 	return (0);
// }

// int ft_check_middle(char *str)
// {
// 	int i;
// 	int	len;

// 	len = (int)ft_strlen(str);
// 	i = 0;
// 	while (str[i] && i < len)
// 	{
// 		if (i > 0)
// 		{
// 			if (str[i] == '2' && (str[i - 1] != '1' && str[i - 1] != '2'))
// 			{
// 				printf("map not closed in column %d.\n", i);
// 				return(1);
// 			}
// 			if (str[i] == '2' && (str[i + 1] != '1' && str[i + 1] != '2' 
				// && str[i + 1] != '\0'))
// 			{
// 				printf("map not closed in column %d.\n", i);
// 				return(1);
// 			}
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// int ft_check_first_pos(char *str)
// {
// 	if (str[0] != '1' && str[0] != '2')
// 	{
// 		printf("first pos not closed\n");
// 		return (1);
// 	}
// 	return (0);
// }

// get pos xy of player
// raycasting loop: go through every x, start at playa pos,
