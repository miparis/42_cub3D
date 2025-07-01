/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <saragar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:11:37 by miparis           #+#    #+#             */
/*   Updated: 2025/07/01 17:10:47 by saragar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>

# define G	"\033[1;32m"
# define Y	"\033[0;33m"
# define R	"\033[0;31m"
# define BB	"\033[1;34m"
# define P	"\033[1;35m"
# define B	"\033[1m"
# define NC	"\033[0m"

typedef struct	s_argument			t_argument;
typedef struct	s_config_flags		t_config_flags;
typedef struct	s_config			t_config;
typedef struct  s_data				t_data;
typedef struct  s_textures			t_textures;
typedef struct  s_player			t_player;
typedef struct  s_img				t_img;

# define TILE_SIZE 64
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720
# define FOV 0.66

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

struct s_textures
{
	void	*no_texture;
	void	*so_texture;
	void	*we_texture;
	void	*ea_texture;
};

struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x; //vector direccion a la que esta mirando el jugador 
	double	dir_y; //vector direccion a la que esta mirando el jugador 
	double	plane_x; //vector perpendicular a la direccion, determina el campo de vision
	double	plane_y; //vector perpendicular a la direccion, determina el campo de vision
};

struct s_img
{
	int		bpp; //bits per pixel
	int		line_len; //bytes ocupados por cada linea de pixeles en la img
	int		endian; //endianness de la imagen
	int		width;
	int		height;
	int		scale_y;
	int		scale_x;
};

struct s_data
{
	void		*mlx_ptr;
	void		*w_ptr;
	void		*img_ptr;
	void		*img_data; //puntero al inicio del bufer de la imagen
	t_player	*player;
	t_textures	*textures;
	t_argument	*map;
	t_config	*config;	
	t_img		*img;
};

/*								UTILS													*/
int	error_msg(const char *error);

/*								PARSE 												*/
int	general_parse(char **argv, t_argument *map_arguments);
int top_bottom(t_argument *arg_map);
int lateral_borders(t_argument *arg_map);
int	open_file(t_argument *arg_map);
int	copy_path(char *line, char **text_path, bool *flag);
int	parse_color(char *line, int *color_dest, bool *flag);
int	map_population(t_argument *arg_map);
int	parse_config(t_argument *arg_map, t_config *config, t_config_flags *flags);
int	check_file(char *file, t_argument *arg_map);
int	object_player_validation(char *line, t_argument *arg_map);

/* 							GRAPHICS									*/
int	set_graphics(t_data *data, t_argument *arg);
int	calculate_coordanates(t_data *data);
int	upload_textures(t_data *data, t_textures *textures, t_config *cfig);
int	init_window(t_data *data, t_argument *arg);

/*				PLAYER										*/
int	set_position(t_data *data);
int	set_orientation(t_data *data);

/*				RAYCASTER										*/
int	set_minimap(t_data *data);

/* 								MEMORY ALLOC & SETTING                 */
int	alloc_set(t_config **config, t_config_flags **flags, t_argument *arg);
int load_arg(t_argument *arg_map, char **argv);
int	map_memory(t_argument *arg_map);

/* 								CLEANING						 */
void	free_all(t_argument *arg_map, t_config *config);
void	free_args(t_argument *arg_map);
void	free_config(t_config *config);
void	free_flags(t_config_flags *flags);
void	free_data(t_data *data);

/*							TEST						*/
void print_all(t_argument *arg_map, t_config *config);


/*		hola miranda no se donde meter estas funciones perdon		*/
int	key_control(int keycode, t_data *data);
int go_exit(t_data *data);
#endif
