/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:35:59 by miparis           #+#    #+#             */
/*   Updated: 2025/07/18 23:31:48 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	parse_colors(char *line, t_config *config,
	t_config_flags *flags, t_argument *arg_map)
{
	if (ft_strncmp(line, "C", 1) == 0)
	{
		arg_map->line_count++;
		if (parse_color(line, &config->ceiling_color, &flags->ceiling))
			return (1);
	}
	else if (ft_strncmp(line, "F", 1) == 0)
	{
		arg_map->line_count++;
		if (parse_color(line, &config->floor_color, &flags->floor))
			return (1);
	}
	return (0);
}

static int	parse_paths(char *line, t_config *config, t_config_flags *flags)
{
	if (ft_strncmp(line, "NO", 2) == 0)
	{
		if (copy_path(line, &config->no_path, &flags->no))
			return (1);
	}
	else if (ft_strncmp(line, "SO", 2) == 0)
	{
		if (copy_path(line, &config->so_path, &flags->so))
			return (1);
	}
	else if (ft_strncmp(line, "WE", 2) == 0)
	{
		if (copy_path(line, &config->we_path, &flags->we))
			return (1);
	}
	else if (ft_strncmp(line, "EA", 2) == 0)
	{
		if (copy_path(line, &config->ea_path, &flags->ea))
			return (1);
	}
	return (0);
}

static int	check_config(char *line, t_argument *arg_map,
		t_config *cf, t_config_flags *flags)
{
	if (!ft_strncmp(line, "NO", 2) || !(ft_strncmp(line, "SO", 2))
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
	{
		arg_map->line_count++;
		if (parse_paths(line, cf, flags))
			return (free(line), 1);
	}
	if (!ft_strncmp(line, "C", 1) || !ft_strncmp(line, "F", 1))
	{
		if (parse_colors(line, cf, flags, arg_map))
			return (free(line), 1);
	}
	return (0);
}

int	parse_config(t_argument *arg_map, t_config *cf, t_config_flags *flags)
{
	char	*line;
	char	*aux_line;
	int		i;

	if (open_file(arg_map))
		return (1);
	line = get_next_line(arg_map->fd);
	while (line != NULL)
	{
		i = 0;
		while (line[i] == ' ' || (line[i] >= 9 && line[i] <= 13))
			i++;
		aux_line = ft_strtrim(line + i, " \t\r\n");
		free(line);
		line = aux_line;
		if (check_config(line, arg_map, cf, flags))
			return (free(line), 1);
		free(aux_line);
		line = get_next_line(arg_map->fd);
	}
	return (0);
}
