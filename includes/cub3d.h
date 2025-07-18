/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:11:37 by miparis           #+#    #+#             */
/*   Updated: 2025/07/18 12:09:59 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# define G	"\033[1;32m"
# define Y	"\033[0;33m"
# define R	"\033[0;31m"
# define BB	"\033[1;34m"
# define P	"\033[1;35m"
# define B	"\033[1m"
# define NC	"\033[0m"

typedef struct s_argument			t_argument;
typedef struct s_config_flags		t_config_flags;
typedef struct s_config				t_config;
typedef struct s_data				t_data;
typedef struct s_textures			t_textures;
typedef struct s_player				t_player;
typedef struct s_img				t_img;
typedef struct s_ray				t_ray;

# define TILE_SIZE 64
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600

# define NUM_RAYS 100000
# define RAY_STEP 0.05
# define M_PI 3.14159265358979323846
# define FOV 0.785398163398
# define M_SPEED 0.1 
# define R_SPEED 0.05

struct s_config_flags
{
	bool	no;
	bool	so;
	bool	we;
	bool	ea;
	bool	floor;
	bool	ceiling;
};

struct s_config
{
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	int				floor_color;
	int				ceiling_color;
	t_config_flags	*set;
};

struct s_argument
{
	char		*file;
	int			fd;
	char		**map;
	int			map_start;
	int			line_count;
	int			player_count;
	char		orientation;
	size_t		width;
	size_t		height;
	t_config	*config;
};

struct s_img
{
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
	int		scale_y;
	int		scale_x;
	void	*img_ptr;
	char	*addr;
};

struct s_textures
{
	t_img	no_tex;
	t_img	so_tex;
	t_img	we_tex;
	t_img	ea_tex;
};

struct s_player
{
	double	angle;
	double	angle_flag;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
};

struct s_data
{
	void		*mlx_ptr;
	void		*w_ptr;
	void		*img_ptr;
	void		*img_data;
	t_player	*player;
	t_textures	*textures;
	t_argument	*map;
	t_config	*config;	
	t_img		*img;
};

struct s_ray
{
	// Variables used in raycasting init
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;

	// Variables used in DDA calc
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;

	//DDA results
	bool	hit;
	int		side;
	double	perp_wall_dist;

	//Coordenate textuures
	double	wall_hit_x;
	double	wall_hit_y;
	double	wall_x_text;
	double	wall_y_text;
};

/*************** 		UTILS				*********************************/
int		error_msg(const char *error);
int		go_exit(t_data *data);

/*************** 		PARSING 			*********************************/
int		general_parse(char **argv, t_argument *map_arguments);
int		top_bottom(t_argument *arg_map);
int		lateral_borders(t_argument *arg_map);
int		open_file(t_argument *arg_map);
int		copy_path(char *line, char **text_path, bool *flag);
int		parse_color(char *line, int *color_dest, bool *flag);
int		map_population(t_argument *arg_map);
int		parse_config(t_argument *arg_map, t_config *cf, t_config_flags *flags);
int		check_file(char *file, t_argument *arg_map);
int		object_player_validation(char *line, t_argument *arg_map);

/* 							GRAPHICS						*/
int		set_graphics(t_data *data, t_argument *arg);
int		calculate_coordanates(t_data *data);
int		upload_textures(t_data *data, t_textures *textures, t_config *cfig);
int		init_window(t_data *data);

/*				PLAYER										*/
int		set_position(t_data *data);
int		set_orientation(t_data *data);

/*************** 		RAYCASTER 			********************************/

/*				MOVEMENT									*/
void	rotate_camera(t_data *data, int keycode);
int		update_position(t_data *data, double x, double y);
int		touch(t_data *data, int px, int py);
int		key_control(int keycode, t_data *data);

/*				DDA											*/
void	dda_init(t_data *data, int screen_x, t_ray *ray);
void	dda_calc(t_ray *ray);
void	dda_loop(t_data *data, t_ray *ray);

/*				DRAW										*/
void	put_floor_ceiling(t_data *game);
void	put_pixel(t_data *data, int x, int y, int color);
void	draw_line(t_data *game, int start_x);
void	draw_limits(t_ray *ray);
void	draw_ray(t_data *game, t_ray *ray, float start_x);
void	draw_texture_column(t_data *data, t_ray *ray, int x, t_img *texture);
void	calc_texture_wall(t_ray *ray, int current_width);

/*				GAME										*/
void	clear_image(t_data *game);
int		game_loop(t_data *game);

/* 					MEMORY ALLOC & SETTING                 */
int		alloc_set(t_config **config, t_config_flags **flags, t_argument *arg);
int		load_arg(t_argument *arg_map, char **argv);
int		map_memory(t_argument *arg_map);

/* 								CLEANING					*/
void	free_all(t_argument *arg_map, t_config *config);
void	free_args(t_argument *arg_map);
void	free_config(t_config *config);
void	free_flags(t_config_flags *flags);
void	free_data(t_data *data);

/*************** 		TEST 						*********************/
void	print_all(t_argument *arg_map, t_config *config);

#endif
