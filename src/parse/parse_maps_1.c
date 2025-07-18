/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_maps_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:03:27 by miparis           #+#    #+#             */
/*   Updated: 2025/07/19 00:00:43 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	skip_header_lines(t_argument *arg_map)
{
	char	*line;
	size_t	i;
	int		j;

	i = 0;
	line = get_next_line(arg_map->fd);
	while (i < (size_t)arg_map->line_count)
	{
		j = 0;
		if (!line)
			return (error_msg("Error: Unexpected end of file before map\n"), 1);
		while (line[j] == ' ' || (line[j] >= 9 && line[j] <= 13))
			j++;
		if (!line[j])
		{
			free(line);
			line = get_next_line(arg_map->fd);
			continue ;
		}
		free(line);
		line = get_next_line(arg_map->fd);
		i++;
	}
	free(line);
	return (0);
}

static void	fill_map_row(t_argument *arg_map, size_t row, char *line)
{
	size_t	len;
	size_t	j;

	len = ft_strlen(line);
	j = 0;
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

static int	check_map(t_argument *arg_map)
{
	if (arg_map->map == NULL)
		return (error_msg("\nError: Memory allocation failed for map\n"), 1);
	return (0);
}

int	prepare_map(t_argument *arg_map)
{
	if (map_memory(arg_map))
		return (1);
	if (open_file(arg_map))
		return (1);
	if (skip_header_lines(arg_map))
	{
		close(arg_map->fd);
		return (1);
	}
	return (0);
}

int	map_population(t_argument *arg_map)
{
	char	*line;
	size_t	i;
	int		j;

	i = 0;
	if (prepare_map(arg_map))
		return (1);
	line = get_next_line(arg_map->fd);
	while (line && i < arg_map->height)
	{
		j = 0;
		while (line[j] == ' ' || (line[j] >= 9 && line[j] <= 13))
			j++;
		if (!line[j])
		{
			free(line);
			line = get_next_line(arg_map->fd);
			continue ;
		}
		fill_map_row(arg_map, i, line);
		free(line);
		line = get_next_line(arg_map->fd);
		i++;
	}
	return (free(line), check_map(arg_map));
}
