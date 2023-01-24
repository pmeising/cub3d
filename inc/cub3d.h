/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmeising <pmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:48:27 by pmeising          #+#    #+#             */
/*   Updated: 2023/01/24 09:48:35 by pmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "stdio.h"
# include "unistd.h"
# include "stdlib.h"
# include <math.h>
# include <../minilibx-linux/mlx.h>
# include <../libft_lib/libft.h>
# define HEIGHT		1070
# define WIDTH		1900
# define W_RED		0x00FF0000
# define W_GREEN	0x0000FF00
# define W_YELLOW	0x00FFFF00
# define W_BLUE		0x000000FF
# define SPEED		0.4

typedef struct s_ray
{
	double	*raydir;
	int		line_height;
	double	camerax;
	double	*deltadist;
	double	*sidedist;
	int		*map;
	int		*step;
	double	perpwalldist;
	int		hit;
	int		side;
	int		pos_start;
	int		pos_end;
	int		texx;
	int		texy;
	double	wallx;
	double	tex_y_step;
}				t_ray;

typedef struct s_img
{
	void	*img;
	char	*addy_img;
	int		height[1];
	int		width[1];
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_prgrm
{
	t_ray			*ray;
	t_img			*img;
	t_img			*img_2;
	t_img			*img_wall_north;
	t_img			*img_wall_south;
	t_img			*img_wall_east;
	t_img			*img_wall_west;
	t_img			*img_wall_door;
	int				qubit;
	int				argc;
	int				window_height;
	int				window_width;
	int				player_num;
	int				map_error;
	double			*playa;
	double			*dir;
	double			*old_dir;
	double			*camera_vector;
	double			*old_camera_vector;
	double			time;
	double			old_time;
	int				map_columns;
	int				map_rows;
	char			*path_to_map;
	char			*path_to_north;
	char			*path_to_south;
	char			*path_to_west;
	char			*path_to_east;
	char			*floor_colour;
	char			*ceiling_colour;
	char			**map;
	void			*mlx;
	void			*mlx_win;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
}				t_prgrm;

// hook functions
void			ft_hooks(t_prgrm *vars);
int				ft_key_hook(int keycode, t_prgrm *vars);
int				ft_close_program(t_prgrm *vars);

// map read functions
void			ft_parsing(t_prgrm *vars);
int				ft_check_map_closed(t_prgrm *vars);
int				ft_is_closed(t_prgrm *vars);
int				ft_has_playa(t_prgrm *vars);
void			ft_is_map_complete(t_prgrm *vars);
int				ft_check_first_last(char *str, int count);
int				ft_check_top_bottom(char *str, int count);
void			ft_buffer_map(t_prgrm *vars);
void			ft_buffer_helper(int dif, t_prgrm *vars, int i);
unsigned int	ft_rgb_to_hex(char *color);
void			ft_mirror_map_2(t_prgrm *vars);

// free funcs
void			ft_free(void *cont);
void			ft_free_all(t_prgrm *vars);
void			ft_free_all_2(t_prgrm *vars);
int				ft_close_program(t_prgrm *vars);
int				ft_close_program_2(t_prgrm *vars);
void			ft_path_exist(t_prgrm *vars);

// Raycasting
void			ft_raycasting(t_prgrm *vars);
void			ft_init_dir_vec(t_prgrm *vars, char c);
void			ft_init_vecs(t_prgrm *vars, char c);
void			ft_raycast(t_prgrm *vars);
void			ft_init_img(t_prgrm *vars);
void			ft_init_img_2(t_prgrm *vars);
void			ft_init_ray(t_prgrm *vars, t_img *img, \
t_img *img_2, t_ray *ray);
void			ft_init_ray_2(t_prgrm *vars);
void			find_texture_coord(t_prgrm *vars, int height);
void			ft_put_wall(t_prgrm *vars, t_img *img, int x, int y);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
void			ft_helper_rotate(t_prgrm *vars, int i);
void			ft_put_image(t_prgrm *vars, t_img *img, int x);
void			ft_calc_ray_dist(t_prgrm *vars);
void			ft_calc_ray_dist_helper(t_prgrm *vars);
void			ft_calc_line_height(t_prgrm *vars);
void			ft_init_raycast(t_prgrm *vars, int x);
void			ft_init_raycast_2(t_prgrm *vars);
void			ft_resize_tex_south(t_prgrm *vars, t_img *img, int x, int y);
void			ft_resize_tex_north(t_prgrm *vars, t_img *img, int x, int y);
void			ft_resize_tex_west(t_prgrm *vars, t_img *img, int x, int y);
void			ft_resize_tex_east(t_prgrm *vars, t_img *img, int x, int y);
void			ft_resize_door(t_prgrm *vars, t_img *img, int x, int y);

// utils
void			ft_check(t_prgrm *vars, void *con, int code);
void			ft_helper_rotate(t_prgrm *vars, int i);
void			print_map(t_prgrm *vars);
int				ft_movement(int keycode, t_prgrm *vars);
#endif