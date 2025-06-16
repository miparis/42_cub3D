/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_maps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:03:27 by miparis           #+#    #+#             */
/*   Updated: 2025/06/16 15:38:50 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	map_memory(t_argument *arg_map)
{
	size_t	i;

	i = 0;
	arg_map->map = ft_calloc((arg_map->height + 1), sizeof(char *));
	if (!arg_map->map)
		return (error_msg("\nError: Memory allocation failed\n"), 1);
	while (i < arg_map->height)
	{
		arg_map->map[i] = ft_calloc((arg_map->width + 1), sizeof(char));
		if (!arg_map->map[i])
		{
			while (arg_map->map[i])
				free(arg_map->map[i]);
			free(arg_map->map);
			error_msg("Error: Memory allocation failed\n");
			return (1);
		}
		i++;
	}
	arg_map->map[i] = NULL;
	return (0);
}

static int	skip_header_lines(t_argument *arg_map)
{
	char	*line;
	size_t	i = 0;

	while (i < (size_t)arg_map->line_count + 2)
	{
		line = get_next_line(arg_map->fd);
		if (!line)
			return (error_msg("Error: Unexpected end of file before map\n"), 1);
		free(line);
		i++;
	}
	return (0);
}

static void	fill_map_row(t_argument *arg_map, size_t row, char *line)
{
	size_t	len = ft_strlen(line);
	size_t	j = 0;

	if (line[len - 1] == '\n')
		len--;

	while (j < len)
	{
		arg_map->map[row][j] = line[j];
		j++;
	}
	while (j < arg_map->width)
	{
		arg_map->map[row][j] = ' ';
		j++;
	}
	arg_map->map[row][arg_map->width] = '\0';
}

int	map_population(t_argument *arg_map)
{
	char	*line;
	size_t	i;

	i = 0;
	if (map_memory(arg_map) || open_file(arg_map))
		return (1);

	if (skip_header_lines(arg_map))
		return (close(arg_map->fd), 1);

	line = get_next_line(arg_map->fd);
	while (line && i < arg_map->height)
	{
		if (!line[0])
		{
			free(line);
			line = get_next_line(arg_map->fd);
			continue;
		}
		fill_map_row(arg_map, i, line);
		free(line);
		line = get_next_line(arg_map->fd);
		i++;
	}
	free(line);
	return (close(arg_map->fd), 0);
}

static int	check_open_tile(char **map, size_t i, size_t start, size_t end)
{
	size_t	j;

	j = start;
	while (j < end)
	{
		if (ft_strchr("0NSEW", map[i][j]))
		{
			if (i == 0 || !map[i + 1] || j == 0 ||
				!map[i][j + 1] || !map[i][j - 1] ||
				map[i - 1][j] == ' ' || map[i + 1][j] == ' ' ||
				map[i][j - 1] == ' ' || map[i][j + 1] == ' ' ||
				map[i - 1][j] == '\0' || map[i + 1][j] == '\0' ||
				map[i][j - 1] == '\0' || map[i][j + 1] == '\0')
				return (1);
		}
		j++;
	}
	return (0);
}

int top_bottom(t_argument *arg_map)
{
	size_t i;

	i = 0;
	while (i < arg_map->width)
	{
		if (arg_map->map[0][i] != '1' && arg_map->map[0][i] != ' ')
			return (error_msg("\nError: Top border must be closed\n"), 1);
		if (arg_map->map[arg_map->height - 1][i] != '1' && arg_map->map[arg_map->height - 1][i] != ' ')
			return (error_msg("\nError: Bottom border must be closed\n"), 1);
		i++;
	}
	return (0);
}

int lateral_borders(t_argument *arg_map)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	**map_copy;

	map_copy = arg_map->map;
	i = 0;
	while (i < arg_map->height)// Salteamos las lineas vacias y espacios inermedios
	{
		start = 0;
		end = ft_strlen(arg_map->map[i]);
		while (start < end && arg_map->map[i][start] == ' ')
			start++;
		while (end > start && arg_map->map[i][end - 1] == ' ')
			end--;
		if (arg_map->map[i][start] != '1' || arg_map->map[i][end - 1] != '1')//verificacion de laterales basico
			return (error_msg("\nError: Side not closed\n"), 1);
		if (check_open_tile(map_copy, i, start, end)) //verificacion de laterales abiertos
			return (error_msg("\nError: Open tile found\n"), 1);
		i++;
	}
	return (0);
}

int	open_file(t_argument *arg_map)
{
	arg_map->fd = open(arg_map->file, O_RDONLY);
	if (arg_map->fd < 0)
		return (error_msg("\nInexisting or unaccesible map file\n"), 1);
	return (0);
}
void print_all(t_argument *arg_map, t_config *config)
{
	size_t i;

	printf("NO PATH = %s\n", config->no_path);
	printf("SO PATH = %s\n", config->so_path);
	printf("WE PATH = %s\n", config->we_path);
	printf("EA PATH = %s\n", config->ea_path);
	printf("FLOOR COLOR = %d\n", config->floor_color);
	printf("CEILING COLOR = %d\n", config->ceiling_color);
	if (!arg_map->map)
	{
		printf("No map loaded.\n");
		return;
	}
	printf("\nMap:\n");
	for (i = 0; i < arg_map->height; i++)
	{
		printf("%s\n", arg_map->map[i]);
	}
	printf("\n");
}