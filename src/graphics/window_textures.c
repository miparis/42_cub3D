/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 15:41:18 by miparis           #+#    #+#             */
/*   Updated: 2025/07/12 12:28:01 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	init_window(t_data *data)
{
	size_t	width;
	size_t	height;

	width = SCREEN_WIDTH;
	height = SCREEN_HEIGHT;
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

	//Se modifico la estructura para que cada textura tenga toda la info necesaria para ser usada
	//falta repetir para cada textura
	
	/*						NO TEXTURE										*/
	textures->no_texture.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
		cfig->no_path, &width, &height);
	if (!textures->no_texture.img_ptr)
		return (error_msg("\nError: Failed to load NO texture\n"), 1);
	textures->no_texture.addr = mlx_get_data_addr(textures->no_texture.img_ptr,
		&textures->no_texture.bpp, &textures->no_texture.line_len, &textures->no_texture.endian);
	if (!textures->no_texture.addr)
		return (error_msg("\nError: Failed to get NO texture data address\n"), 1);
	textures->no_texture.width = width;
	textures->no_texture.height = height;
	/*						SO TEXTURE										*/

	textures->so_texture.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
		cfig->so_path, &width, &height);
	if (!textures->so_texture.img_ptr)
		return (error_msg("\nError: Failed to load SO texture\n"), 1);
	textures->so_texture.addr = mlx_get_data_addr(textures->so_texture.img_ptr,
		&textures->so_texture.bpp, &textures->so_texture.line_len, &textures->so_texture.endian);
	if (!textures->so_texture.addr)
		return (error_msg("\nError: Failed to get SO texture data address\n"), 1);
	textures->so_texture.width = width;
	textures->so_texture.height = height;
	/*						EA TEXTURE										*/
	textures->ea_texture.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
		cfig->ea_path, &width, &height);
	if (!textures->ea_texture.img_ptr)
		return (error_msg("\nError: Failed to load EA texture\n"), 1);
	textures->ea_texture.addr = mlx_get_data_addr(textures->ea_texture.img_ptr,
		&textures->ea_texture.bpp, &textures->ea_texture.line_len, &textures->ea_texture.endian);
	if (!textures->ea_texture.addr)
		return (error_msg("\nError: Failed to get EA texture data address\n"), 1);
	textures->ea_texture.width = width;
	textures->ea_texture.height = height;
	/*						WE TEXTURE										*/
	textures->we_texture.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
		cfig->we_path, &width, &height);
	if (!textures->we_texture.img_ptr)
		return (error_msg("\nError: Failed to load WE texture\n"), 1);
	textures->we_texture.addr = mlx_get_data_addr(textures->we_texture.img_ptr,
		&textures->we_texture.bpp, &textures->we_texture.line_len, &textures->we_texture.endian);
	if (!textures->we_texture.addr)
		return (error_msg("\nError: Failed to get WE texture data address\n"), 1);
	textures->we_texture.width = width;
	textures->we_texture.height = height;
	return (0);
}

int	calculate_coordanates(t_data *data)
{
	(void)data;
	printf("Calculating player coordinates...\n");
	return (0);
}