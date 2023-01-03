/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:48:27 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/03 18:04:06 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "stdio.h"
# include "unistd.h"
# include "stdlib.h"
# include "math.h"
# include <../minilibx-linux/mlx.h>
# include <../libft_lib/libft.h>

typedef struct s_prgrm
{
	int		argc;
	double	*playa;
	double	*direction;
	double	*plane;
	double	time;
	double	old_time;
	int		map_columns;
	int		map_rows;
	char	*path_to_map;
	char	*path_to_north;
	char	*path_to_south;
	char	*path_to_west;
	char	*path_to_east;
	char	*floor_colour;
	char	*ceiling_colour;
	char	**map;
	void	*mlx;
	void	*mlx_win;
}				t_prgrm;

// hook functions
void	ft_hooks(t_prgrm *vars);
int		ft_key_hook(int keycode, t_prgrm *vars);
int		ft_close_program(t_prgrm *vars);

// map read functions
void	ft_parsing(t_prgrm *vars);
int 	ft_check_map_closed(t_prgrm *vars);
int		ft_is_closed(t_prgrm *vars);
int		ft_has_playa(t_prgrm *vars);
void	ft_is_map_complete(t_prgrm *vars);

// free funcs
void	ft_free(void *cont);
void	ft_free_all(t_prgrm *vars);
int		ft_close_program(t_prgrm *vars);

int	ft_check_first_last(char *str, int count);

#endif