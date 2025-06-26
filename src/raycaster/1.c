/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:39:03 by miparis           #+#    #+#             */
/*   Updated: 2025/06/26 13:02:15 by miparis          ###   ########.fr       */
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

	//printf("\n  WIDTH = [%zu] - HEIGHT = [%zu]\n", data->map->width, data->map->height);
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

	row = 0;
	while (row < (int)data->map->height)
	{
		col = 0;
		while (col < (int)data->map->width)
		{
			if (data->map->map[row][col] == '1')
				color = data->config->ceiling_color;
			else
				color = data->config->floor_color;
			y = 0;
			while (y < TILE_SIZE)
			{
				x = 0;
				while (x < TILE_SIZE)
				{
					put_pixel(data, col * TILE_SIZE + x, row * TILE_SIZE + y, color);
					x++;
				}
				y++;
			}
			col++;
		}
		row++;
	}
}

static void	draw_player(t_data *data)
{
	int i;
	int j;
	int px;
	int py;

	px = data->player->pos_x * TILE_SIZE;
	py = data->player->pos_y * TILE_SIZE;
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			put_pixel(data, px + j, py + i, 0xFF0000); // rojo
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
	double	dx;
	double	dy;
	int		x;
	int		y;

	px = data->player->pos_x * TILE_SIZE;
	py = data->player->pos_y * TILE_SIZE;
	dx = data->player->dir_x;
	dy = data->player->dir_y;
	i = 0;
	while (i < 20)
	{
		x = px + dx * i;
		y = py + dy * i;
		put_pixel(data, x, y, 0x00FF00); // verde
		i++;
	}
}

int	set_minimap(t_data *data)
{
	draw_minimap(data);
	draw_player(data);
	draw_direction(data);
	mlx_put_image_to_window(data->mlx_ptr, data->w_ptr, data->img_ptr, 0, 0);
	return (0);
}
