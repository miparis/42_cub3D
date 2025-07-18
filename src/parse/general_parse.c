/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:04:43 by miparis           #+#    #+#             */
/*   Updated: 2025/07/18 23:55:15 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// static int	check_lines(t_argument *arg_map)
// {
// 	int		i;
// 	char	*line;

// 	i = 0;
// 	while (i < (arg_map->line_count + 1))
// 	{
// 		line = get_next_line(arg_map->fd);
// 		if (!line)
// 		{
// 			error_msg("Error: Unexpected end of file before map\n");
// 			return (free(line), 1);
// 		}
// 		free(line);
// 		i++;
// 	}
// 	return (0);
// }

static void	process_dimensions_line(char *line, t_argument *arg_map, int *aux_h)
{
	size_t	line_len;
	int		i;

	i = 0;
	while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
		i++;
	if (line[i] == '\0')
		return ;
	line_len = ft_strlen(line);
	if (line[line_len - 1] == '\n')
		line_len--;
	if (line_len > arg_map->width)
		arg_map->width = line_len;
	(*aux_h)++;
}

static int	object_validation(t_argument *arg_map)
{
	int	i;

	i = 0;
	while (arg_map->map[i])
	{
		if (object_player_validation(arg_map->map[i], arg_map))
			return (1);
		i++;
	}
	return (0);
}

static int	calculate_dimension(t_argument *arg_map)
{
	char	*line;
	int		aux_height;

	aux_height = 0;
	if (open_file(arg_map))
		return (1);
	line = get_next_line(arg_map->fd);
	while (line)
	{
		process_dimensions_line(line, arg_map, &aux_height);
		free(line);
		line = get_next_line(arg_map->fd);
	}
	aux_height -= arg_map->line_count;
	arg_map->height = aux_height;
	if (arg_map->width == 0 || arg_map->height == 0)
	{
		error_msg("Error: Empty or invalid map\n");
		return (close(arg_map->fd), 1);
	}
	return (close(arg_map->fd), 0);
}

int	general_parse(char **argv, t_argument *arg_map)
{
	t_config		*config;
	t_config_flags	*flags;

	if (load_arg(arg_map, argv))
		return (1);
	if (check_file(argv[1], arg_map))
		return (free_args(arg_map), 1);
	alloc_set(&config, &flags, arg_map);
	if (parse_config(arg_map, config, flags))
		return (free_all(arg_map, config), 1);
	if (!flags->no || !flags->so || !flags->we || !flags->ea
		|| !flags->floor || !flags->ceiling)
	{
		error_msg("\nError: Missing texture path or color config\n");
		return (free_all(arg_map, config), 1);
	}
	if (calculate_dimension(arg_map))
		return (free_all(arg_map, config), 1);
	if ((map_population(arg_map)))
		return (free_all(arg_map, config), 1);
	if (object_validation(arg_map))
		return (close(arg_map->fd), free_all(arg_map, config), 1);
	if ((top_bottom(arg_map) || lateral_borders(arg_map)))
		return (free_all(arg_map, config), 1);
	return (close(arg_map->fd), 0);
}
