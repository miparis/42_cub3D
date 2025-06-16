/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:17:04 by miparis           #+#    #+#             */
/*   Updated: 2025/06/16 15:43:20 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int load_arg(t_argument *arg_map, char **argv)
{
	if (argv[1])
		arg_map->file = argv[1];
	else
		arg_map->file = NULL;
	arg_map->fd = 0;
	arg_map->map = NULL;
	arg_map->map_start = 0;
	arg_map->line_count = 0;
	arg_map->width = 0;
	arg_map->height = 0;
	return (0);
}

int alloc_set(t_config *config, t_config_flags *flags)
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

