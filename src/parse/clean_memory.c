/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:40:36 by miparis           #+#    #+#             */
/*   Updated: 2025/06/20 12:18:17 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_args(t_argument *arg_map)
{
	if (arg_map->map)
	{
		free_split(arg_map->map);
		arg_map->map = NULL;
	}
}

void	free_flags(t_config_flags *flags)
{
	if (!flags)
		return ;
	if (flags)
		free(flags);
}

void	free_config(t_config *config)
{
	if (config->no_path)
		free(config->no_path);
	if (config->so_path)
		free(config->so_path);
	if (config->we_path)
		free(config->we_path);
	if (config->ea_path)
		free(config->ea_path);
	if (config)
		free(config);
}

void	free_all(t_argument *arg_map, t_config *config)
{
	if (config->set)
		free_flags(config->set);
	if (config)
		free_config(config);
	if (arg_map)
		free_args(arg_map);
}
