/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:53:49 by saragar2          #+#    #+#             */
/*   Updated: 2025/07/03 17:33:58 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	update_position(t_data *data, double x, double y)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos_x + x;
	new_y = data->player->pos_y + y;
	if (!touch(data, data->player->pos_y, new_x))
		data->player->pos_x = new_x;
	if (!touch(data, new_y, data->player->pos_x))
		data->player->pos_y = new_y;
	return (0);
}

int	touch(t_data *data, int px_map_y, int py_map_x)
{
    // Asegurarse de que las coordenadas estén dentro de los límites válidos del mapa.
    // px_map_y es la fila (Y) y py_map_x es la columna (X).
    // Primero, verifica que la fila (py_map_y) sea válida antes de intentar obtener su longitud.
	if (px_map_y < 0 || px_map_y >= (int)data->map->height)
		return (1);
    // Comprueba los límites horizontales (py_map_x)
	if (py_map_x < 0 || py_map_x >= (int)ft_strlen(data->map->map[px_map_y]))
		return (1);
	if (data->map->map[px_map_y][py_map_x] == '1')
		return (1); 
	return (0);
}

int	key_control(int keycode, t_data *data)
{
	if (keycode == 65307) //"ESC"
		go_exit(data);
	else if (keycode == 119) //W
		update_position(data, cos(data->player->angle) * M_SPEED,
			sin(data->player->angle) * M_SPEED);
	else if (keycode == 115) // S
		update_position(data, cos(data->player->angle) * -M_SPEED,
			sin(data->player->angle)* -M_SPEED);
	else if (keycode == 100) //D
		update_position(data, sin(data->player->angle) * -M_SPEED,
			cos(data->player->angle) * M_SPEED);
	else if (keycode == 97) //A
		update_position(data, sin(data->player->angle) * M_SPEED,
			cos(data->player->angle) * -M_SPEED);
	if (keycode == 65361) // Izquierda
		data->player->angle_flag -= R_SPEED;
	if (keycode == 65363) // Derecha
		data->player->angle_flag += R_SPEED;
	set_minimap(data);
	return (0);
}

void	draw_rays(t_data *data)
{
	double	angle_start;
	double	angle;
	double	ray_x;
	double	ray_y;
	int		i;

	// Calcula el ángulo actual del jugador usando su vector de dirección
	data->player->angle = atan2(data->player->dir_y, data->player->dir_x) + data->player->angle_flag;

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
