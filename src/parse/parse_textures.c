/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:35:59 by miparis           #+#    #+#             */
/*   Updated: 2025/06/12 12:10:17 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int alloc_set(t_config *config, t_config_flags *flags)
{
	ft_bzero(config, sizeof(t_config));
	ft_bzero(flags, sizeof(t_config_flags));
	config->no_path = NULL;
	config->so_path = NULL;
	config->we_path = NULL;
	config->ea_path = NULL;
	config->floor_color = -1;
	config->ceiling_color = -1;
	flags->no = false;
	flags->so = false;
	flags->we = false;
	flags->ea = false;
	flags->floor = false;
	flags->ceiling = false;
	return (0);
}
static int parse_colors(char *line, t_config *config, t_config_flags *flags)
{
	if (ft_strncmp(line, "F", 1) == 0)
	{
		if (parse_color(line, &config->floor_color, &flags->floor))
            return (free(line), 1);
		printf(" --> FLOOR COLOR = %d\n", config->floor_color);
		free(line);
    }
	else if (ft_strncmp(line, "C", 1) == 0)
    {
		if (parse_color(line, &config->ceiling_color, &flags->ceiling))
			return (free(line), 1);
		printf(" --> CEILING COLOR = %d\n", config->ceiling_color);
        free(line);
    }
	return (0);
}

static int parse_paths(char *line, t_config *config, t_config_flags *flags)
{
    if (ft_strncmp(line, "NO", 2) == 0)
    {
            if (copy_path(line, &config->no_path, &flags->no))
                return (free(line), 1);
            printf(" --> NO PATH = %s\n", config->no_path);
			free(line);
    }
    else if (ft_strncmp(line, "SO", 2) == 0)
    {
        if (copy_path(line, &config->so_path, &flags->so))
            return (free(line), 1);
        printf(" --> SO PATH = %s\n", config->so_path);
        free(line);
    }
    else if (ft_strncmp(line, "WE", 2) == 0)
    {
        if (copy_path(line, &config->we_path, &flags->we))
            return (free(line), 1);
        printf(" --> WE PATH = %s\n", config->we_path);
        free(line);
    }
    else if (ft_strncmp(line, "EA", 2) == 0)
    {
        if (copy_path(line, &config->ea_path, &flags->ea))
            return (free(line), 1);
		printf(" --> EA PATH = %s\n", config->ea_path);
        free(line);
        }
    return (0);
}

int	parse_config(t_argument *arg_map)
{
    t_config		config;
    t_config_flags	flags;
    char			*line;

    alloc_set(&config, &flags);
    if (open_file(arg_map))
        return (1);
    while ((line = get_next_line(arg_map->fd)))
    {
        if (line[0] == '\n')
            free(line); // solo libera y NO hace nada más
        else if ((ft_strncmp(line, "NO", 2) == 0) || (ft_strncmp(line, "SO", 2) == 0) ||
            ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0 )
        {
            if (parse_paths(line, &config, &flags))
                return (1);
        }
		if (ft_strncmp(line, "C", 1) == 0 || ft_strncmp(line, "F", 1) == 0)
		{
            if (parse_colors(line, &config, &flags))
		 		return (1);
        }
    }
    if (!flags.no || !flags.so || !flags.we || !flags.ea || !flags.floor || !flags.ceiling)
        return (error_msg("\nError: Missing texture path or color config\n"), 1);
    return (0);
}
