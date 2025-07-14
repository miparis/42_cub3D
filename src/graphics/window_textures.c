/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <saragar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:41:18 by miparis           #+#    #+#             */
/*   Updated: 2025/07/14 19:36:01 by saragar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_window(t_data *data)
{
	size_t	width;
	size_t	height;

	width = SCREEN_WIDTH;
	height = SCREEN_HEIGHT;
	data->w_ptr = mlx_new_window(data->mlx_ptr, SCREEN_WIDTH,
			SCREEN_HEIGHT, "Cub3D");
	if (!data->w_ptr)
		return (error_msg("\nError: Failed to create window\n"), 1);
	data->img_ptr = mlx_new_image(data->mlx_ptr, width, height);
	if (!data->img_ptr)
		return (error_msg("\nError: Failed to create image\n"), 1);
	data->img_data = mlx_get_data_addr(data->img_ptr, &data->img->bpp,
			&data->img->line_len,
			&data->img->endian);
	if (!data->img_data)
		return (error_msg("\nError: Failed to get image data address\n"), 1);
	data->img->width = SCREEN_WIDTH;
	data->img->height = SCREEN_HEIGHT;
	return (0);
}

static int	upload_north_south(t_data *data, t_textures *tex, t_config *cfig)
{
	int		height;
	int		width;

	tex->no_tex.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
			cfig->no_path, &width, &height);
	if (!tex->no_tex.img_ptr)
		return (error_msg("\nError: Failed to load NO tex\n"), 1);
	tex->no_tex.addr = mlx_get_data_addr(tex->no_tex.img_ptr,
			&tex->no_tex.bpp, &tex->no_tex.line_len, &tex->no_tex.endian);
	if (!tex->no_tex.addr)
		return (error_msg("\nError: Failed to get NO tex data address\n"), 1);
	tex->no_tex.width = width;
	tex->no_tex.height = height;
	tex->so_tex.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
			cfig->so_path, &width, &height);
	if (!tex->so_tex.img_ptr)
		return (error_msg("\nError: Failed to load SO tex\n"), 1);
	tex->so_tex.addr = mlx_get_data_addr(tex->so_tex.img_ptr,
			&tex->so_tex.bpp, &tex->so_tex.line_len, &tex->so_tex.endian);
	if (!tex->so_tex.addr)
		return (error_msg("\nError: Failed to get SO tex data address\n"), 1);
	tex->so_tex.width = width;
	tex->so_tex.height = height;
	return (0);
}

static int	upload_east_west(t_data *data, t_textures *tex, t_config *cfig)
{
	int		height;
	int		width;

	tex->ea_tex.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
			cfig->ea_path, &width, &height);
	if (!tex->ea_tex.img_ptr)
		return (error_msg("\nError: Failed to load EA tex\n"), 1);
	tex->ea_tex.addr = mlx_get_data_addr(tex->ea_tex.img_ptr,
			&tex->ea_tex.bpp, &tex->ea_tex.line_len, &tex->ea_tex.endian);
	if (!tex->ea_tex.addr)
		return (error_msg("\nError: Failed to get EA tex data address\n"), 1);
	tex->ea_tex.width = width;
	tex->ea_tex.height = height;
	tex->we_tex.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
			cfig->we_path, &width, &height);
	if (!tex->we_tex.img_ptr)
		return (error_msg("\nError: Failed to load WE tex\n"), 1);
	tex->we_tex.addr = mlx_get_data_addr(tex->we_tex.img_ptr,
			&tex->we_tex.bpp, &tex->we_tex.line_len, &tex->we_tex.endian);
	if (!tex->we_tex.addr)
		return (error_msg("\nError: Failed to get WE tex data address\n"), 1);
	tex->we_tex.width = width;
	tex->we_tex.height = height;
	return (0);
}

int	upload_textures(t_data *data, t_textures *textures, t_config *cfig)
{
	if (upload_north_south(data, textures, cfig) == 1)
		return (1);
	if (upload_east_west(data, textures, cfig) == 1)
		return (1);
	return (0);
}

int	calculate_coordanates(t_data *data)
{
	(void)data;
	printf("Calculating player coordinates...\n");
	return (0);
}
