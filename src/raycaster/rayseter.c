/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayseter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:39:03 by miparis           #+#    #+#             */
/*   Updated: 2025/07/10 16:46:58 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// /*
// y * img->line_len: Te posiciona al inicio de la fila y dentro del buffer.
// Si cada línea ocupa 800 bytes y estás en la fila 3, esto salta 3 * 800 = 2400 bytes.
// x * (img->bpp / 8): Dentro de esa fila, salta x píxeles.
// Como cada píxel ocupa bpp / 8 bytes, multiplicás para moverte horizontalmente.
// Suma total: Obtenés un puntero dst al byte exacto donde está el píxel en (x, y) en la imagen.
// */

void put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;


	if (x < 0 || y < 0 || x >= data->img->width || y >= data->img->height)
		return ;
	dst = data->img_data + (y * data->img->line_len + x * (data->img->bpp / 8));
	*(unsigned int *)dst = color;
	
}

//-------DEBUG---------
// void	draw_rays(t_data *data)
// {
// 	double	angle_start;
// 	double	angle;
// 	double	ray_x;
// 	double	ray_y;
// 	int		i;

// 	// Calcula el ángulo actual del jugador usando su vector de dirección
// 	data->player->angle = atan2(data->player->dir_y, data->player->dir_x) + data->player->angle_flag;

// 	// Centro del FOV basado en dirección del jugador
// 	double dir_angle = data->player->angle; // en radianes
// 	angle_start = dir_angle - (FOV * M_PI / 180.0) / 2.0;

// 	for (i = 0; i < NUM_RAYS; i++)
// 	{
// 		angle = angle_start + i * ((FOV * M_PI / 180.0) / NUM_RAYS);
// 		ray_x = data->player->pos_x;
// 		ray_y = data->player->pos_y;

// 		// Avanza el rayo poco a poco
// 		while (1)
// 		{
// 			int map_x = (int)ray_x;
// 			int map_y = (int)ray_y;

// 			// Verifica si el rayo toca una pared
// 			if (touch(data, map_y, map_x)) // NOTA: Y antes que X
// 				break;

// 			// Dibuja el rayo en el minimapa
// 			int px = ray_x * data->img->scale_x;
// 			int py = ray_y * data->img->scale_y;

// 			// Dibuja solo si está dentro de los límites de la imagen
// 			if (px >= 0 && px < data->img->width && py >= 0 && py < data->img->height)
// 				put_pixel(data, px, py, 0x00FF00); // verde

// 			ray_x += cos(angle) * RAY_STEP;
// 			ray_y += sin(angle) * RAY_STEP;
// 		}
// 	}
// }

// static void draw_minimap(t_data *data)
// {
// 	int	x;
// 	int	y;
// 	int row;
// 	int col;
// 	int color;
	
// 	row = -1;
// 	while (++row < (int)data->map->height)
// 	{
// 		col = -1;
// 		while (++col < (int)data->map->width)
// 		{
// 			if (data->map->map[row][col] == '1')
// 				color = data->config->ceiling_color;
// 			else
// 				color = data->config->floor_color;
// 			y = -1;
// 			while (++y < data->img->scale_y)
// 			{
// 				x = -1;
// 				while (++x < data->img->scale_x)
// 					put_pixel(data, (col * data->img->scale_x + x), (row * data->img->scale_y + y) , color);
// 			}
// 		}
// 	}
// }
//---------------------
int	set_minimap(t_data *data)
{
	draw_loop(data);
	//-------DEBUG---------
	// draw_minimap(data);
	// draw_rays(data);
	//---------------------
	return (0);
}
