/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_maps_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <saragar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:03:27 by miparis           #+#    #+#             */
/*   Updated: 2025/07/18 18:43:33 by saragar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	object_player_validation(char *line, t_argument *arg_map)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (!ft_strchr("01NSEW ", line[i]))
			return (error_msg("\nError: Invalid char found in map\n"), 1);
		if (ft_strchr("NSEW", line[i]))
		{
			arg_map->player_count++;
			arg_map->orientation = line[i];
			if (arg_map->player_count > 1)
				return (error_msg("\nError: More than one player\n"), 1);
		}
		i++;
	}
	return (0);
}

static int	check_open_tile(char **map, size_t i, size_t start, size_t end)
{
	size_t	j;

	j = start;
	while (j < end)
	{
		if (ft_strchr("0NSEW", map[i][j]))
		{
			if (i == 0 || !map[i + 1] || j == 0 || !map[i][j + 1]
				|| !map[i][j - 1] ||
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

int	top_bottom(t_argument *arg_map)
{
	size_t	i;

	i = 0;
	while (i < arg_map->width)
	{
		if (arg_map->map[0][i] != '1' && arg_map->map[0][i] != ' ')
			return (error_msg("\nError: Top border must be closed\n"), 1);
		if (arg_map->map[arg_map->height - 1][i] != '1' &&
			arg_map->map[arg_map->height - 1][i] != ' ')
			return (error_msg("\nError: Bottom border must be closed\n"), 1);
		i++;
	}
	return (0);
}

int	lateral_borders(t_argument *arg_map)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	**map_copy;

	map_copy = arg_map->map;
	i = 0;
	while (i < arg_map->height)
	{
		start = 0;
		end = ft_strlen(arg_map->map[i]);
		while (start < end && arg_map->map[i][start] == ' ')
			start++;
		while (end > start && arg_map->map[i][end - 1] == ' ')
			end--;
		if (arg_map->map[i][start] != '1' || arg_map->map[i][end - 1] != '1')
			return (error_msg("\nError: Side not closed\n"), 1);
		if (check_open_tile(map_copy, i, start, end))
			return (error_msg("\nError: Open tile found\n"), 1);
		i++;
	}
	return (0);
}
