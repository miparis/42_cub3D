/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:03:27 by miparis           #+#    #+#             */
/*   Updated: 2025/06/12 15:59:43 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void print_map(t_argument *arg_map)
{
	size_t i;

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

int top_bottom(t_argument *arg_map)
{
	size_t i;

	i = 0;
	print_map(arg_map);
	while (i < arg_map->width)
	{
		if (arg_map->map[0][i] != '1' && arg_map->map[0][i] != ' ')
		{
			printf("\n ----> CHAR NOT CLOSED %c\n", arg_map->map[0][i]);
			printf("DEBUG index: %zu\n", i);
			return (error_msg("\nError: Top border must be closed\n"), 1);
		}
		if (arg_map->map[arg_map->height - 1][i] != '1' && arg_map->map[arg_map->height - 1][i] != ' ')
		{
			printf("\n ----> CHAR NOT CLOSED %c\n", arg_map->map[arg_map->height - 1][i]);
			return (error_msg("\nError: Bottom border must be closed\n"), 1);
		}
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
		printf("DEBUG line: %s\n", arg_map->map[i]);
		if (arg_map->map[i][start] != '1' || arg_map->map[i][end - 1] != '1')
		{
			printf("\n ----> CHAR NOT CLOSED %c\n", arg_map->map[i][start]);
			if (!arg_map->map[i][end - 1])
				printf("Invalid char:  null character at end of line\n");
			else if (arg_map->map[i][end - 1] == '\n')
				printf("Invalid char:  newline character at end of line\n");
			if (!arg_map->map[i][start])
				printf("Invalid char:  null character at start of line\n");
			else if (arg_map->map[i][start] == '\n')
				printf("Invalid char:  newline character at end of line\n"); 
			return (error_msg("\nError: Side not closed\n"), 1);
		}
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