/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:22:01 by miparis           #+#    #+#             */
/*   Updated: 2025/07/16 11:02:11 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	open_file(t_argument *arg_map)
{
	arg_map->fd = open(arg_map->file, O_RDONLY);
	if (arg_map->fd < 0)
		return (error_msg("\nInexisting or unaccesible map file\n"), 1);
	return (0);
}

int	check_file(char *file, t_argument *arg_map)
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

void	print_all(t_argument *arg_map, t_config *config)
{
	size_t	i;

	(void)config;
	if (!arg_map->map)
	{
		printf("No map loaded.\n");
		return ;
	}
	printf("\nMap:\n");
	i = -1;
	while (++i < arg_map->height)
		printf("%s\n", arg_map->map[i]);
	printf("\n");
	printf("NO PATH = %s\n", config->no_path);
	printf("SO PATH = %s\n", config->so_path);
	printf("WE PATH = %s\n", config->we_path);
	printf("EA PATH = %s\n", config->ea_path);
	printf("FLOOR COLOR = %d\n", config->floor_color);
	printf("CEILING COLOR = %d\n", config->ceiling_color);
	printf("Orientation: %c\n", arg_map->orientation);
}
