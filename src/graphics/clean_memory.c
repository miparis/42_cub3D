/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <saragar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 11:28:47 by miparis           #+#    #+#             */
/*   Updated: 2025/07/14 19:38:04 by saragar2         ###   ########.fr       */
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
	if (textures->no_tex.img_ptr != NULL)
		mlx_destroy_image(data->mlx_ptr, textures->no_tex.img_ptr);
	if (textures->so_tex.img_ptr != NULL)
		mlx_destroy_image(data->mlx_ptr, textures->so_tex.img_ptr);
	if (textures->we_tex.img_ptr != NULL)
		mlx_destroy_image(data->mlx_ptr, textures->we_tex.img_ptr);
	if (textures->ea_tex.img_ptr != NULL)
		mlx_destroy_image(data->mlx_ptr, textures->ea_tex.img_ptr);
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
