/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:48:27 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/05 18:51:47 by pmeising         ###   ########.fr       */
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
# define HEIGHT 540
# define WIDTH 960

typedef struct	s_ray
{
	double	*rayDir;
	double	cameraX;
	double	*deltaDist;
	double	*sideDist;
	double	perpWallDist; // perpendicular wall distance
	int		*map;
	int		*step;
	int		hit;
	int		side;
	int		pos_start;
	int		pos_end;
}				t_ray;

typedef struct s_img
{
	void	*img;
	// void	*mlx;
	char	*addy_img;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_prgrm
{
	t_ray	*ray;
	t_img	*img;
	t_img	*img_2;
	int		argc;
	int		window_height;
	int		window_width;
	int		player_num;
	double	*playa;
	double	*direction;
	double	*camera_vector;
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
	unsigned int	floor_color;
	unsigned int	ceiling_color;
}				t_prgrm;

// hook functions
void			ft_hooks(t_prgrm *vars);
int				ft_key_hook(int keycode, t_prgrm *vars);
int				ft_close_program(t_prgrm *vars);

// map read functions
void			ft_parsing(t_prgrm *vars);
int 			ft_check_map_closed(t_prgrm *vars);
int				ft_is_closed(t_prgrm *vars);
int				ft_has_playa(t_prgrm *vars);
void			ft_is_map_complete(t_prgrm *vars);
int				ft_check_first_last(char *str, int count);
int				ft_check_top_bottom(char *str, int count);
void			ft_buffer_map(t_prgrm *vars);
void			ft_buffer_helper(int dif, t_prgrm *vars, int i);
unsigned int	ft_rgb_to_hex(char *color);

// free funcs
void			ft_free(void *cont);
void			ft_free_all(t_prgrm *vars);
int				ft_close_program(t_prgrm *vars);

// Raycasting
void			ft_raycasting(t_prgrm *vars);
void			ft_init_dir_vec(t_prgrm *vars, char c);
void			ft_init_vecs(t_prgrm *vars, char c);

#endif