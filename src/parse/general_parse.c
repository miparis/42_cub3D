/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:04:43 by miparis           #+#    #+#             */
/*   Updated: 2025/06/16 16:04:42 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_lines(t_argument *arg_map)
{
	int		i;
	char	*line;
	
	i = 0;
	while (i < (arg_map->line_count + 1))
	{
		line = get_next_line(arg_map->fd);
		if (!line)
			return (error_msg("Error: Unexpected end of file before map\n"), free(line), 1);
		free(line);
		i++;
	}
	return (0);
}

static void	process_dimensions_line(char *line, t_argument *arg_map, int *aux_height)
{
	size_t	line_len;

	if (line[0] == '\n')
		return ;
	line_len = ft_strlen(line);
	if (line[line_len - 1] == '\n')
		line_len--;
	if (line_len > arg_map->width)
		arg_map->width = line_len;
	(*aux_height)++;
}

static int	check_file(char *file, t_argument *arg_map)
{
	const char	*ext;
	size_t		file_len;
	size_t		ext_len;
	char		*file_ext;

	ext = ".cub";
	file_len = ft_strlen(file);
	ext_len = ft_strlen(ext);
	if (open_file(arg_map))
		return (1);
	if (file_len < ext_len)
	{
		close(arg_map->fd);
		return (error_msg("\n Map file with wrong extension\n"), 1);
	}
	file_ext = ft_substr(file, file_len - ext_len, ext_len);
	if (ft_strcmp(file_ext, ext) != 0)
	{
		free(file_ext);
		close(arg_map->fd);
		return (error_msg("\n Map file with wrong extension\n"), 1);
	}
	free(file_ext);
	return (0);
}

static int	object_validation(t_argument *arg_map)
{
	char	*line;
	int		player_count;
	int		i;

	player_count = 0;
	if (open_file(arg_map))
		return (1);
	check_lines(arg_map);
	line = get_next_line(arg_map->fd);
	while (line != NULL)
	{
		i = -1;
		while (line[++i] && line[i] != '\n')
		{
			if (!ft_strchr("01NSEW ", line[i]))
				return (free(line), close(arg_map->fd), error_msg("\nError: Invalid char\n"), 1);
			if (ft_strchr("NSEW", line[i]))
				player_count++;
		}
		free(line);
		line = get_next_line(arg_map->fd);
	}
	if (player_count != 1)
		return (error_msg("\nError: Multiple or none players\n"), 1);
	return (close(arg_map->fd), 0);
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
		return (error_msg("Error: Empty or invalid map\n"), close(arg_map->fd), 1);
	return (close(arg_map->fd), 0);
}

int	general_parse(int argc, char **argv, t_argument arg_map)
{
    t_config		config;
    t_config_flags	flags;
	
	if (argc < 2)
		return (error_msg("\nMissing argument\n"), 1);
	load_arg(&arg_map, argv);
	if (check_file(argv[1], &arg_map))
		return (free_args(&arg_map), 1);
	alloc_set(&config, &flags);
	if (parse_config(&arg_map, &config, &flags))
		return (free_all(&arg_map, &config), 1);
	if (!flags.no || !flags.so || !flags.we || !flags.ea || !flags.floor || !flags.ceiling)
    	return (error_msg("\nError: Missing texture path or color config\n"), free_config(&config), 1);
	if (object_validation(&arg_map))
		return (free_all(&arg_map, &config), 1);
	if (calculate_dimension(&arg_map))
		return (free_all(&arg_map, &config), 1);
	if ((map_population(&arg_map)))
		return (free_all(&arg_map, &config), 1);
	if (!arg_map.map)
		return(error_msg("\nFailed to load map\n"),free_all(&arg_map, &config), 1);
	if ((top_bottom(&arg_map) || lateral_borders(&arg_map)))
		return (free_all(&arg_map, &config), 1);
	close(arg_map.fd);
	//print_all(&arg_map, &config);
	//free_all(&arg_map, &config);
	return (0);
}

