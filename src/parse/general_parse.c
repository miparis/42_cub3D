/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:04:43 by miparis           #+#    #+#             */
/*   Updated: 2025/06/02 20:35:31 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_file(char *file, t_argument *arg_map)
{
	const char	*ext;
	size_t		file_len;
	size_t		ext_len;
	char		*file_ext;

	ext = ".cub";
	file_len = ft_strlen(file);
	ext_len = ft_strlen(ext);
	arg_map->fd = open(arg_map->file, O_RDONLY);
	if (arg_map->fd < 0)
		return (error_msg("\nInexisting map file\n"), 1);
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

int	object_validation(t_argument *arg_map)
{
	char	*line;
	int		player_count;
	int		i;

	player_count = 0;
	while ((line = get_next_line(arg_map->fd)))
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
	}
	if (player_count != 1)
		return (error_msg("\nError: Only one player allowed\n"), 1);
	return (0);
}


int	general_parse(int argc, char **argv, t_argument *arg_map)
{
	if (argc < 2)
		return (error_msg("\nMissing argument\n"), 1);
	arg_map->file = argv[1];
	if (check_file(argv[1], arg_map))
		return (1);
	if (object_validation(arg_map))
		return (1);
	return (0);
}

