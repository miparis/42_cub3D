/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:03:27 by miparis           #+#    #+#             */
/*   Updated: 2025/06/12 12:18:44 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
	size_t i;
	size_t start;
	size_t end;

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
			return (error_msg("\nError: Map not closed\n"), 1);
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