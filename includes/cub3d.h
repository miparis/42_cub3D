/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:11:37 by miparis           #+#    #+#             */
/*   Updated: 2025/06/05 11:43:47 by miparis          ###   ########.fr       */
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

struct s_argument
{
	char	*file;
	int		fd;
	char	**map;
	char	**copy;
	size_t	width;
	size_t	height;
};

/*								UTILS													*/
int	error_msg(const char *error);

/*								PARSE													*/
int	general_parse(int argc, char **argv, t_argument map_arguments);

#endif
