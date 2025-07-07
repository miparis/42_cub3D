/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <saragar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:53:49 by saragar2          #+#    #+#             */
/*   Updated: 2025/07/07 15:23:06 by saragar2         ###   ########.fr       */
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
		{data->player->angle_flag += R_SPEED; printf("DEBUG DERECHAZO HISTAORICOOOOOOO-------------------------\n\n");}
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

// static void cast_ray_column(t_data *data, double ray_angle, int i)
// {
// 	double ray_x = data->player->pos_x;
// 	double ray_y = data->player->pos_y;
// 	double step_size = 0.01;
// 	double cos_angle = cos(ray_angle);
// 	double sin_angle = sin(ray_angle);

// 	// Avanza hasta encontrar pared
// 	while (!touch(data, (int)ray_y, (int)ray_x))
// 	{
// 		ray_x += cos_angle * step_size;
// 		ray_y += sin_angle * step_size;
// 	}

// 	// Distancia real
// 	double dist = sqrt((ray_x - data->player->pos_x) * (ray_x - data->player->pos_x) +
// 	                   (ray_y - data->player->pos_y) * (ray_y - data->player->pos_y));

// 	// Corrección fish-eye
// 	double corrected_dist = dist * cos(ray_angle - data->player->angle);

// 	// Distancia al plano de proyección (fórmula estándar)
// 	double fov_rad = FOV * M_PI / 180.0;
// 	double proj_plane_dist = (SCREEN_WIDTH / 2.0) / tan(fov_rad / 2.0);

// 	// Altura en pantalla
// 	int wall_height = (int)((TILE_SIZE / corrected_dist) * proj_plane_dist);

// 	// Rango vertical de la columna
// 	int start_y = (SCREEN_HEIGHT / 2) - (wall_height / 2);
// 	int end_y = start_y + wall_height;

// 	if (start_y < 0) start_y = 0;
// 	if (end_y > SCREEN_HEIGHT) end_y = SCREEN_HEIGHT;

// 	int color = 0xAAAAAA;

// 	for (int y = start_y; y < end_y; y++)
// 		put_pixel(data, i, y, color);
// }


static void draw_line(t_player *player, t_data *game, float start_x, int i)
{
    float cos_angle = cos(start_x);
    float sin_angle = sin(start_x);
    float ray_x = player->pos_x;
    float ray_y = player->pos_y;

    while(!touch(game, ray_x, ray_y))
    {
        ray_x += cos_angle;
        ray_y += sin_angle;
    }
	float dist = (fixed_dist(player->pos_x, player->pos_y, ray_x, ray_y, game)) * 10;
	printf("DEBUG-----------DIST=%f\n", dist);
	// sleep(1);
	float height = (TILE_SIZE / dist) * (SCREEN_WIDTH / 2);
	int start_y = (SCREEN_HEIGHT - height) / 2;
	int end = start_y + height;
	printf("DEBUG-----------END=%d   START_Y=%d\n", end, start_y);
	printf("HOLA\n");
	while(start_y < end)
	{
		put_pixel(game, i, start_y, 0xff0000);
		start_y++;
	}
	printf("Hola\n");
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
	// player->angle = atan2(player->dir_y, player->dir_x) + player->angle_flag;
	// player->angle = M_PI / 2;
	player->angle += player->angle_flag;
    clear_image(game);
    float fraction = M_PI / 3 / SCREEN_WIDTH;
    float start_x = player->angle - M_PI / 6;
    int i = 0;
    while(i < SCREEN_WIDTH)
    {
		player->angle_flag = 0;
        draw_line(player, game, start_x, i);
		printf("DEBUG-----------START_X=%f\n", start_x);
        start_x += fraction;
        i++;
		printf("DEBUG-----------I=%d\n", i);
    }

	if (game->mlx_ptr == NULL || game->w_ptr == NULL || game->img == NULL)
	{
		printf("\nError: Failed to allocate MLX, window or image\n");
		exit (1);
	}
    mlx_put_image_to_window(game->mlx_ptr, game->w_ptr, game->img_ptr, 0, 0);
	printf("DEBUG-----------DRAW LOOP COMPLETED\n");
    return 0;
}


// void	draw_rays(t_data *data, double ray_angle, int j)
// {
// 	double	angle_start;
// 	double	angle;
// 	// double	ray_x;
// 	// double	ray_y;
// 	int		i;
// 	(void)ray_angle; //quitar
// 	(void)j; //quitar

// 	// Calcula el ángulo actual del jugador usando su vector de dirección
// 	data->player->angle = atan2(data->player->dir_y, data->player->dir_x) + data->player->angle_flag;

// 	// Centro del FOV basado en dirección del jugador
// 	double dir_angle = data->player->angle; // en radianes
// 	angle_start = dir_angle - (FOV * M_PI / 180.0) / 2.0;

// 	for (i = 0; i < NUM_RAYS; i++)
// 	{
// 		angle = angle_start + i * ((FOV * M_PI / 180.0) / NUM_RAYS);
// 		// ray_x = data->player->pos_x;
// 		// ray_y = data->player->pos_y;

// 		cast_ray_column(data, angle, i);
	// 	// Avanza el rayo poco a poco
	// 	while (1)
	// 	{
	// 		int map_x = (int)ray_x;
	// 		int map_y = (int)ray_y;

	// 		// Verifica si el rayo toca una pared
	// 		if (touch(data, map_y, map_x)) // NOTA: Y antes que X
	// 			break;

	// 		// Dibuja el rayo en el minimapa
	// 		int px = ray_x * data->img->scale_x;
	// 		int py = ray_y * data->img->scale_y;

	// 		// Dibuja solo si está dentro de los límites de la imagen
	// 		if (px >= 0 && px < data->img->width && py >= 0 && py < data->img->height)
	// 			put_pixel(data, px, py, 0x00FF00); // verde

	// 		ray_x += cos(angle) * RAY_STEP;
	// 		ray_y += sin(angle) * RAY_STEP;
	// 	}
	// 	float dist = fixed_dist(data->player->pos_x, data->player->pos_y, ray_x, ray_y, data);
	// 	float height = (TILE_SIZE / dist) * (SCREEN_WIDTH / 2);
	// 	int start_y = (SCREEN_HEIGHT - height) / 2;
	// 	int end = start_y + height;
	// 	while(start_y < end)
	// 	{
	// 		put_pixel(data, i, start_y, 255);
	// 		start_y++;
	// 	}
// 	}
	
// }