/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <saragar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:53:49 by saragar2          #+#    #+#             */
/*   Updated: 2025/07/09 17:47:44 by saragar2         ###   ########.fr       */
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
	{
		printf("collision, px_map_y: %i\n", px_map_y);
		return (1);
	}
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
	mlx_put_image_to_window(data->mlx_ptr, data->w_ptr, data->img_ptr, 0, 0);
	set_minimap(data);
	return (0);
}

float distance(float x, float y){
    return sqrt(x * x + y * y);
}

float fixed_dist(float x1, float y1, float x2, float y2, t_data *game)
{
    float delta_x = x2 - x1;
    float delta_y = y2 - y1;
   	float angle = atan2(delta_y, delta_x) - game->player->angle;
    float fix_dist = distance(delta_x, delta_y) * cos(angle);
    return fix_dist;
}

static void draw_line(t_player *player, t_data *game, float start_x, int i)
{
    float cos_angle = cos(start_x);
    float sin_angle = sin(start_x);
    float ray_x = player->pos_x;
    float ray_y = player->pos_y;
	float fov_y = FOV * SCREEN_HEIGHT / SCREEN_WIDTH;
	float proj_plane_height = 2 * tan(fov_y / 2);
	
    while(!touch(game, ray_y, ray_x))
    {
        ray_x += cos_angle * 0.02; //esto y lo de abajo es lo que se usa para suavizar los bordes/ojo de pez
        ray_y += sin_angle * 0.02;
    }
	float dist = (fixed_dist(player->pos_x, player->pos_y, ray_x, ray_y, game));
	float height = ((1 / dist) / (proj_plane_height) * SCREEN_HEIGHT);

	float start_y = (SCREEN_HEIGHT - height) / 2;
	float end = start_y + height;
	while(start_y < end)
	{
		put_pixel(game, i, start_y, 0xff0000);
		start_y++;
	}
}

static void clear_image(t_data *game)
{
    for(int y = 0; y < SCREEN_HEIGHT; y++)
        for(int x = 0; x < SCREEN_WIDTH; x++)
            put_pixel(game, x, y, 0);
}

int draw_loop(t_data *game)
{
    t_player *player = game->player;
	
	player->angle += player->angle_flag;
    clear_image(game);
    float fraction = FOV / SCREEN_WIDTH;
    float start_x = player->angle - FOV / 2;
    int i = 0;
    while(i < SCREEN_WIDTH)
    {
		player->angle_flag = 0;
        draw_line(player, game, start_x, i);
        start_x += fraction;
        i++;
    }

	if (game->mlx_ptr == NULL || game->w_ptr == NULL || game->img == NULL)
	{
		printf("\nError: Failed to allocate MLX, window or image\n");
		exit (1);
	}
    return 0;
}
