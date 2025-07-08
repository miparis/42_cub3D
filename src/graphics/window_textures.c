/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <saragar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:41:18 by miparis           #+#    #+#             */
/*   Updated: 2025/07/08 22:02:34 by saragar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_window(t_data *data)
{
	size_t	width;
	size_t	height;

	width = SCREEN_WIDTH;
	height = SCREEN_HEIGHT;
	printf("\n  WIDTH = [%zu] - HEIGHT = [%zu]\n", width, height);
	data->w_ptr = mlx_new_window(data->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
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

//pasar textures a img dese el path de xmp en config
int	upload_textures(t_data *data, t_textures *textures, t_config *cfig)
{
	int		height;
	int		width;

	textures->no_texture = mlx_xpm_file_to_image(data->mlx_ptr,
		cfig->no_path, &width, &height);
	if (!textures->no_texture)
		return (error_msg("\nError: Failed to load NO texture\n"), 1);
	textures->so_texture = mlx_xpm_file_to_image(data->mlx_ptr,
		cfig->so_path, &width, &height);
	if (!textures->so_texture)
		return (error_msg("\nError: Failed to load SO texture\n"), 1);
	textures->ea_texture = mlx_xpm_file_to_image(data->mlx_ptr,
		cfig->ea_path, &width, &height);
	if (!textures->ea_texture)
		return (error_msg("\nError: Failed to load EA texture\n"), 1);
	textures->we_texture = mlx_xpm_file_to_image(data->mlx_ptr,
		cfig->we_path, &width, &height);
	if (!textures->we_texture)
		return (error_msg("\nError: Failed to load WE texture\n"), 1);
	return (0);
}

int	calculate_coordanates(t_data *data)
{
	(void)data;
	printf("Calculating player coordinates...\n");
	return (0);
}