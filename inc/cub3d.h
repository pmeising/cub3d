/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:48:27 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/02 18:29:58 by pmeising         ###   ########.fr       */
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
	char	*path_to_map;
	char	*path_to_north;
	char	*path_to_south;
	char	*path_to_west;
	char	*path_to_east;
	char	*floor_colour;
	char	*ceiling_colour;
	char	**map;
	int		map_columns;
	int		map_rows;
	void	*mlx;
	void	*mlx_win;
}				t_prgrm;

// hook functions
void	ft_hooks(t_prgrm *vars);
int		ft_key_hook(int keycode, t_prgrm *vars);
int		ft_close_program(t_prgrm *vars);

// map read functions
void	ft_parsing(t_prgrm *vars);


// free funcs
void	ft_free(void *cont);
#endif