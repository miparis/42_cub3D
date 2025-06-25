/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 14:49:38 by miparis           #+#    #+#             */
/*   Updated: 2025/06/25 11:17:30 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	set_player(t_data *data)
{
	/*	PLAYER STRUCT */
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		return (error_msg("\Error: Failed to allocate player struct\n"), 1);
	ft_bzero(data->player, sizeof(t_player));
	/*	PLAYER SETTING */
	if (set_position(data))
		return (1);
	if (set_orientation(data))
		return (1);
	printf("Player position set to: (%.2f, %.2f)\n",
		data->player->pos_x, data->player->pos_y);
	printf("Player direction set to: (%.2f, %.2f)\n",
		data->player->dir_x, data->player->dir_y);
	printf("Player plane set to: (%.2f, %.2f)\n",
		data->player->plane_x, data->player->plane_y);
	return (0);
}

static int	set_textures_struct(t_data *data, t_config *config)
{
	/*	TEXTURES STRUCT */
	data->textures = malloc(sizeof(t_textures));
	if (!data->textures)
		return (error_msg("\nError: Failed to allocate textures struct\n"), 1);
	/* XMP TO IMAGE FOR EACH ONE*/
	ft_bzero(data->textures, sizeof(t_textures));
	if (upload_textures(data, data->textures, config))
		return (1);
	return (0);
}

static int	set_data(t_data *data, t_argument *arg, t_config *config)
{
	/*	DATA  STRUCT */
	data->map = arg;
	data->config = config;
	if (!data->map || !data->config)
		return (error_msg("\nError: Failed to allocate map or config struct\n"), 1);
	/*	MXL			*/
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return ((error_msg("\Error: Failed to allocate MLX struct\n"), 1));
	if (init_window(data, arg))
		return (1);
	/*TEXTURES STRUCT*/
	if (set_textures_struct(data, config))
		return (1);
	/*PLAYERS STRUCT*/
	if (set_player(data))
		return (1);
	return (0);
}

int	set_graphics(t_data *data, t_argument *arg)
{
	ft_bzero(data, sizeof(t_data));
	if (!data)
		return (error_msg("\nError: Failed to allocate data struct\n"), 1);
	set_data(data, arg, arg->config);
	return (0);
}