/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:11:37 by miparis           #+#    #+#             */
/*   Updated: 2025/06/12 15:32:32 by miparis          ###   ########.fr       */
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

# define G	"\033[1;32m"
# define Y	"\033[0;33m"
# define R	"\033[0;31m"
# define BB	"\033[1;34m"
# define P	"\033[1;35m"
# define B	"\033[1m"
# define NC	"\033[0m"

typedef struct	s_argument			t_argument;
typedef struct	s_config_flags		t_config_flags;
typedef struct	s_config				t_config;

struct s_config_flags
{
	bool no;
	bool so;
	bool we;
	bool ea;
	bool floor;
	bool ceiling;
};

struct s_config
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color;
	int		ceiling_color;
	t_config_flags set;
};

struct s_argument
{
	char	*file;
	int		fd;
	char	**map;
	char	**copy_map;
	int		map_start;
	int		line_count;
	size_t	width;
	size_t	height;
};

/*								UTILS													*/
int	error_msg(const char *error);

/*								PARSE													*/
int	general_parse(int argc, char **argv, t_argument map_arguments);
int	parse_config(t_argument *arg_map);

/*								PARSE UTILS												*/
int top_bottom(t_argument *arg_map);
int lateral_borders(t_argument *arg_map);
int	open_file(t_argument *arg_map);
int	copy_path(char *line, char **text_path, bool *flag);
int	parse_color(char *line, int *color_dest, bool *flag);
int	load_file(t_argument *arg_map);

#endif
