/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:28:47 by miparis           #+#    #+#             */
/*   Updated: 2025/07/03 17:24:17 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	free_player(t_player *player)
{
	if (!player)
		return ;
	free(player);
}

static void	free_textures(t_data *data, t_textures *textures)
{
	if (!textures)
		return ;
	if (textures->no_texture != NULL)
		mlx_destroy_image(data->mlx_ptr, textures->no_texture);
	if (textures->so_texture != NULL)
		mlx_destroy_image(data->mlx_ptr, textures->so_texture);
	if (textures->we_texture != NULL)
		mlx_destroy_image(data->mlx_ptr, textures->we_texture);
	if (textures->ea_texture != NULL)
		mlx_destroy_image(data->mlx_ptr, textures->ea_texture);
	free(textures);
}

void	free_data(t_data *data)
{
	if (!data)
		return ;
	if (data->mlx_ptr && data->w_ptr)
		mlx_destroy_window(data->mlx_ptr, data->w_ptr);
	if (data->player)
		free_player(data->player);
	if (data && data->textures)
		free_textures(data, data->textures);
	if (data->config->set)
		free_flags(data->config->set);
	if (data->config)
		free_config(data->config);
	if (data->map)
		free_args(data->map);
	if (data->mlx_ptr)
		mlx_destroy_display(data->mlx_ptr);
}