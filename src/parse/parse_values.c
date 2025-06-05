/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:35:59 by miparis           #+#    #+#             */
/*   Updated: 2025/06/05 18:45:20 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int alloc_set(t_config *config, t_config_flags *flags)
{
	ft_bzero(config, sizeof(config));
	ft_bzero(flags, sizeof(flags));
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

static int	copy_path(char *line, char **text_path, bool *flag)
{
	/* Copiar y chequear ruta valida - Si esta correcta cambia su estado*/
	line += 2;
	while (*line && ft_isspace(*line))
		line++;
	if (ft_strncmp(line, "./", 2))
		return (error_msg("\nError: Path must begin with ./\n"), 1);
	//if (the flag passed is not set)
	//we set the path
	//we change the flag to true
	//*line += 3;
	if (*flag)
		return (error_msg("\nError: Duplicated texture\n"), 1);
	*text_path = ft_strdup(line);
	if (!*text_path)
		return (error_msg("\nError: Memory allocation failed\n"), 1);
	printf("Texture path: %s\n", *text_path);
	if (open(*text_path, O_RDONLY) < 0)
		return (error_msg("\nError: Invalid texture path A\n"), 1);
	*flag = true;
	return (0);
}
static char	*remove_spaces_around_commas(char *str)
{
	char	*result;
	int		i = 0, j = 0;

	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == ' ' && (str[i + 1] == ',' || (i > 0 && str[i - 1] == ',')))
			i++;
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

static int	parse_color(char *line, int *color_dest, bool *flag)
{
	char	**rgb;
	int		r, g, b;
	char	*clean;

	if (*flag)
		return (error_msg("Error: Duplicate color identifier\n"), 1);

	line += 1;
	while (*line == ' ' || *line == '\t')
		line++;

	clean = remove_spaces_around_commas(line);
	if (!clean)
		return (error_msg("Error: Memory allocation failed\n"), 1);

	rgb = ft_split(clean, ',');
	free(clean);
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_split(rgb), error_msg("Error: Invalid RGB format\n"), 1);

	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (free_split(rgb), error_msg("Error: RGB value out of range\n"), 1);

	*color_dest = (r << 16) | (g << 8) | b;
	*flag = true;
	free_split(rgb);
	return (0);
}
/*
int	parse_textures(t_argument *arg_map)
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
			free(line);	//continuar a la siguiente linea hasta que encontrar valores
		if (ft_strncmp(line, "NO", 2) == 0 && !flags.no)
			if (copy_path(line, &config.no_path, &flags.no))
				return (free(line), 1);;
		if (ft_strncmp(line, "SO", 2) == 0 && !flags.no)
			if (copy_path(line, &config.so_path, &flags.so))
				return (free(line), 1);
		if (ft_strncmp(line, "WE", 2) == 0 && !flags.no)
			if (copy_path(line, &config.we_path, &flags.we))
				return (free(line), 1);
		if (ft_strncmp(line, "F", 1) == 0 && !flags.floor)
			if (parse_color(line, &config.floor_color, &flags.floor))
				return (free(line), 1);
		if (ft_strncmp(line, "C", 1) == 0 && !flags.ceiling)
			if (parse_color(line, &config.ceiling_color, &flags.ceiling))
				return (free(line), 1);
		if (ft_strncmp(line, "EA", 2) == 0 && !flags.no)
		{
			if (copy_path(line, &config.ea_path, &flags.ea))
				return (free(line), 1);
		}
		else
			return (error_msg("\nError: Invalid orientation\n"), 1);
	}
	free(line);
	if (!flags.no || !flags.so || !flags.we || !flags.ea)
		return (error_msg("\nError: Missing texture path\n"), 1);
	return (0);
}*/
int	parse_textures(t_argument *arg_map)
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
        else if (ft_strncmp(line, "NO", 2) == 0)
        {
            if (copy_path(line, &config.no_path, &flags.no))
                return (free(line), 1);
            free(line);
        }
        else if (ft_strncmp(line, "SO", 2) == 0)
        {
            if (copy_path(line, &config.so_path, &flags.so))
                return (free(line), 1);
            free(line);
        }
        else if (ft_strncmp(line, "WE", 2) == 0)
        {
            if (copy_path(line, &config.we_path, &flags.we))
                return (free(line), 1);
            free(line);
        }
        else if (ft_strncmp(line, "EA", 2) == 0)
        {
            if (copy_path(line, &config.ea_path, &flags.ea))
                return (free(line), 1);
            free(line);
        }
        else if (ft_strncmp(line, "F", 1) == 0)
        {
            if (parse_color(line, &config.floor_color, &flags.floor))
                return (free(line), 1);
            free(line);
        }
        else if (ft_strncmp(line, "C", 1) == 0)
        {
            if (parse_color(line, &config.ceiling_color, &flags.ceiling))
                return (free(line), 1);
            free(line);
        }
        else
        {
            free(line);
            return (error_msg("\nError: Invalid orientation or identifier\n"), 1);
        }
    }
    if (!flags.no || !flags.so || !flags.we || !flags.ea)
        return (error_msg("\nError: Missing texture path\n"), 1);
    return (0);
}