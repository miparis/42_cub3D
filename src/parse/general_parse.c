/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:04:43 by miparis           #+#    #+#             */
/*   Updated: 2025/06/12 16:10:34 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static	int load_arg(t_argument *arg_map)
{
	arg_map->file = NULL;
	arg_map->fd = 0;
	arg_map->map = NULL;
	arg_map->copy_map = NULL;
	arg_map->map_start = 0;
	arg_map->line_count = 0;
	arg_map->width  = 0;
	arg_map->height  = 0;
	return (0);
}

static int	check_file(char *file, t_argument *arg_map)
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

static int	object_validation(t_argument *arg_map)
{
	char	*line;
	int		player_count;
	int		i;

	player_count = 0;
	if (open_file(arg_map))
		return (1);
	i = 0;
	while (i < (arg_map->line_count + 1))
	{
		line = get_next_line(arg_map->fd);
		if (!line)
			return (error_msg("Error: Unexpected end of file before map\n"), free(line), 1);
		free(line);
		i++;
	}
	while ((line = get_next_line(arg_map->fd)))
	{
		i = -1;
		while (line[++i] && line[i] != '\n')
		{
			if (!ft_strchr("01NSEW ", line[i]))
			{
				printf("\nInvalid char: %c\n", line[i]);
				return (free(line), close(arg_map->fd), error_msg("\nError: Invalid char\n"), 1);
			}
			if (ft_strchr("NSEW", line[i]))
				player_count++;
		}
		free(line);
	}
	if (player_count != 1)
		return (error_msg("\nError: Multiple or none players\n"), 1);
	close(arg_map->fd);
	return (0);
}


static int	calculate_dimension(t_argument *arg_map)
{
	char	*line;
	size_t	line_len;
	int		aux_height;

	aux_height = 0;
	if (open_file(arg_map))
		return (1);
	while ((line = get_next_line(arg_map->fd)))
	{
		if (line[0] == '\n') // saltar líneas vacías
		{
			free(line);
			continue; // entramos a la siguiente iteración
		}
		line_len = ft_strlen(line);
		if (line[line_len - 1] == '\n')
			line_len--;  // no contar el salto
		if (line_len > arg_map->width) //actualizamos ancho a la línea más larga
			arg_map->width = line_len;
		aux_height++;
		free(line);
	}
	printf("DEBUG aux_height: %d\n", aux_height);
	aux_height -= arg_map->line_count; // restamos las líneas de la cabecera
	printf("DEBUG line count: %zu\n", (size_t)arg_map->line_count);
	printf("DEBUG aux_height: %d\n", aux_height);
	arg_map->height = aux_height; // restamos las líneas de la cabecera
	printf("\n->Height = [%zu] \n", arg_map->height);
	if (arg_map->width == 0 || arg_map->height == 0)
		return (error_msg("Error: Empty or invalid map\n"), close(arg_map->fd), 1);
	return (close(arg_map->fd), 0);
}

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

static int	map_population(t_argument *arg_map)
{
    char	*line;
    size_t	i, j, len;
    i = 0;

    if (map_memory(arg_map) || open_file(arg_map)){
        return (1);
	}
	while (i < (size_t)arg_map->line_count + 2)
	{
		line = get_next_line(arg_map->fd);
		if (!line)
			return (error_msg("Error: Unexpected end of file before map\n"), free(line), 1);
		free(line);
		i++;
	}
	i = 0;
    while ((line = get_next_line(arg_map->fd)) && i < arg_map->height)
    {
		if (!line[0]) // saltar líneas vacías
			i++;
        len = ft_strlen(line);
        if (line[len - 1] == '\n')
            len--;
        j = 0;
        while (j < len)
        {
            arg_map->map[i][j] = line[j];
            j++;
        }
        while (j < arg_map->width)
        {
            arg_map->map[i][j] = ' ';
            j++;
        }
        arg_map->map[i][arg_map->width] = '\0';
        free(line);
        i++;
    }
    return (free(line), close(arg_map->fd), 0);
}

int	general_parse(int argc, char **argv, t_argument arg_map)
{
	if (argc < 2)
		return (error_msg("\nMissing argument\n"), 1);
	load_arg(&arg_map);
	arg_map.file = argv[1];
	if (check_file(argv[1], &arg_map))
		return (1);
	if (parse_config(&arg_map))
		return (1);
	//SEPARAR LINEAS DEL MAPA DE LA CABECERA
	if (object_validation(&arg_map))
		return (1);
	if (calculate_dimension(&arg_map))
		return (1);
	//printf("->Height = [%zu] \n ->Width = [%zu]\n", arg_map.height, arg_map.width);
	if ((map_population(&arg_map)))
		return (1);
	if (!arg_map.map)
		return(error_msg("\nFailed to load map\n"), 1);
	if ((top_bottom(&arg_map) || lateral_borders(&arg_map)))
		return (1);
	close(arg_map.fd);
	return (0);
}

