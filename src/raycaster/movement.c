/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <saragar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:53:49 by saragar2          #+#    #+#             */
/*   Updated: 2025/07/01 21:11:32 by saragar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	touch(t_data *data, int px, int py)
{
	if (data->map->map[px][py] == '1')
	return (1);
	return (0);
}
// if (px < 0 || py < 0 || (size_t) px >= data->map->width || (size_t) py >= data->map->height)
// 	return (1);

#include <math.h> // Para sin/cos/tan

void	draw_rays(t_data *data)
{
	double	angle_start;
	double	angle;
	double	ray_x;
	double	ray_y;
	int		i;

	// Calcula el ángulo actual del jugador usando su vector de dirección
	data->player->angle = atan2(data->player->dir_y, data->player->dir_x);

	// Centro del FOV basado en dirección del jugador
	double dir_angle = data->player->angle; // en radianes
	angle_start = dir_angle - (FOV * M_PI / 180.0) / 2.0;

	for (i = 0; i < NUM_RAYS; i++)
	{
		angle = angle_start + i * ((FOV * M_PI / 180.0) / NUM_RAYS);
		ray_x = data->player->pos_x;
		ray_y = data->player->pos_y;

		// Avanza el rayo poco a poco
		while (1)
		{
			int map_x = (int)ray_x;
			int map_y = (int)ray_y;

			// Verifica si el rayo toca una pared
			if (touch(data, map_y, map_x)) // NOTA: Y antes que X
				break;

			// Dibuja el rayo en el minimapa
			int px = ray_x * data->img->scale_x;
			int py = ray_y * data->img->scale_y;

			// Dibuja solo si está dentro de los límites de la imagen
			if (px >= 0 && px < data->img->width && py >= 0 && py < data->img->height)
				put_pixel(data, px, py, 0x00FF00); // verde

			ray_x += cos(angle) * RAY_STEP;
			ray_y += sin(angle) * RAY_STEP;
		}
	}
}

