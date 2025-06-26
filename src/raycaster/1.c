/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:39:03 by miparis           #+#    #+#             */
/*   Updated: 2025/06/26 17:28:56 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
y * img->line_len: Te posiciona al inicio de la fila y dentro del buffer.
Si cada línea ocupa 800 bytes y estás en la fila 3, esto salta 3 * 800 = 2400 bytes.
x * (img->bpp / 8): Dentro de esa fila, salta x píxeles.
Como cada píxel ocupa bpp / 8 bytes, multiplicás para moverte horizontalmente.
Suma total: Obtenés un puntero dst al byte exacto donde está el píxel en (x, y) en la imagen.
*/

static void put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

 	if (x < 0 || y < 0 || x >= data->img->width || y >= data->img->height)
	{
		error_msg("\nError: Invalid map dimensions\n");
		return ;
	}
	dst = data->img_data + (y * data->img->line_len + x * (data->img->bpp / 8));
	*(unsigned int *)dst = color;
}

static void draw_minimap(t_data *data)
{
	int	x;
	int	y;
	int row;
	int col;
	int color;
	
	row = -1;
	while (++row < (int)data->map->height)
	{
		col = -1;
		while (++col < (int)data->map->width)
		{
			if (data->map->map[row][col] == '1')
				color = data->config->ceiling_color;
			else
				color = data->config->floor_color;
			y = -1;
			while (++y < data->img->scale_y)
			{
				x = -1;
				while (++x < data->img->scale_x)
					put_pixel(data, (col * data->img->scale_x + x), (row * data->img->scale_x + y) , color);
			}
		}
	}
}

static void	draw_player(t_data *data)
{
	int i;
	int j;
	int px;
	int py;

	px = data->player->pos_x * (SCREEN_WIDTH / data->map->width);
	py = data->player->pos_y * (SCREEN_HEIGHT / data->map->height);
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			put_pixel(data, px + j, py + i, 0xFF0000);// rojo
			j++;
		}
		i++;
	}
}
static void	draw_direction(t_data *data)
{
	int		i;
	int		px;
	int		py;
	int		x;
	int		y;

	px = data->player->pos_x * (SCREEN_WIDTH / data->map->width);
	py = data->player->pos_y * (SCREEN_HEIGHT / data->map->height);
	i = 0;
	while (i < 20)
	{
		x = px +  data->player->dir_x * i;
		y = py + data->player->dir_y * i;
		put_pixel(data, x, y, 0x808080);
		i++;
	}
}
static void	draw_ray(t_data *data, double dir_x, double dir_y)
{
	double		ray_x;
	double		ray_y;
	int			map_x;
	int			map_y;	

	ray_x = data->player->pos_x;
	ray_y = data->player->pos_y;
	while (1)
	{
		map_x = (int)ray_x;
		map_y = (int)ray_y;
		if (data->map->map[map_y][map_x] == '1')
			break; // Si el rayo toca una pared, salimos del bucle
		put_pixel(data, ray_x * data->img->scale_x, ray_y * data->img->scale_y, 0x00FF00); // verde
		ray_x += dir_x * 0.01;
		ray_y += dir_y * 0.1;
	}
}

/*static void draw_fov(t_data *data)
{
	int		i;
	int		camera_x;
	double	ray_dir_y;
	double	ray_dir_x;

	i = 0;
	while (i < SCREEN_WIDTH)
	{
		camera_x = (2 * i / (double)SCREEN_WIDTH) - 1; // Normaliza a [-1, 1]
		ray_dir_x = data->player->dir_x + data->player->plane_x * camera_x;
		ray_dir_y = data->player->dir_y + data->player->plane_y * camera_x;
		draw_ray(data, ray_dir_x, ray_dir_y);
		i++;
	}
}*/

int	set_minimap(t_data *data)
{
	draw_minimap(data);
	draw_player(data);
	draw_direction(data);
	draw_ray(data, data->player->dir_x , data->player->dir_y);
	// draw_fov(data);
	mlx_put_image_to_window(data->mlx_ptr, data->w_ptr, data->img_ptr, 0, 0);
	return (0);
}
