/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:53:49 by saragar2          #+#    #+#             */
/*   Updated: 2025/07/10 17:10:57 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static	void rotate_camera(t_data *data, int keycode)
{
	double old_dir_x;
	double old_plane_x;
	double r_speed;

	r_speed = 0;
	if (keycode == 65363) //izquierda
		r_speed = R_SPEED;
	else if (keycode == 65361) //derecha
		r_speed = -R_SPEED;
	old_dir_x = data->player->dir_x;
	old_plane_x = data->player->plane_x;
	data->player->dir_x = old_dir_x * cos(r_speed) - data->player->dir_y * sin(r_speed);
	data->player->dir_y = old_dir_x * sin(r_speed) + data->player->dir_y * cos(r_speed);
	data->player->plane_x = old_plane_x * cos(r_speed) - data->player->plane_y * sin(r_speed);
	data->player->plane_y = old_plane_x * sin(r_speed) + data->player->plane_y * cos(r_speed);
	data->player->angle += r_speed; //actualiza el angulo del jugador
}


/*Actualizando las corrdenadas del jugador. 
Se chequea las colisiones por celda (X e Y) y luego se actualiza			*/
static int	update_position(t_data *data, double x, double y)
{
	double	new_x;
	double	new_y;

	new_x = data->player->pos_x + x;
	new_y = data->player->pos_y + y;
	if (!touch(data, data->player->pos_y, new_x))
		data->player->pos_x = new_x;
	//esto es lo que permite que eñ jugador se deslize si hay una colision
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
		error_msg("\nError: Collision detected");
		printf("px_map_y: %i\n", px_map_y);
		return (1);
	}
    // Comprueba los límites horizontales (py_map_x)
	if (py_map_x < 0 || py_map_x >= (int)ft_strlen(data->map->map[px_map_y]))
		return (1);
	if (data->map->map[px_map_y][py_map_x] == '1')
		return (1);
	return (0);
}

/*Se encarga de chequear los moviminetos en movimiento y rotacion de vista. Calcula deltaX y deltaY (mediante sin() y coss())*/
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
		rotate_camera(data, 65361);
	if (keycode == 65363) // Derecha
		rotate_camera(data, 65363);
	mlx_put_image_to_window(data->mlx_ptr, data->w_ptr, data->img_ptr, 0, 0);
	set_minimap(data);
	return (0);
}

/*Calcula la distancia euclidiana (la distancia "en línea recta") desde el origen (0,0) hasta un punto (x, y) en un plano 2D.
Obtiene la distancia entre dos puntos (el jugador y el punto de impacto del rayo), pasándole las diferencias de coordenadas delta_x y delta_y.*/
float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

//Calcula la distancia perpendicular desde el jugador al rayo. Corrige ojo de pez
float	fixed_dist(float x1, float y1, float x2, float y2, t_data *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = x2 - x1; //Posicion del jugador para calculo vector de direccion
	delta_y = y2 - y1;//Punto de impacto para calculo vector de lonngitud	
	/*Se calcula el ángulo absoluto del rayo con respecto al eje X. 
	 atan2 devuelve el ángulo en radianes entre el eje X positivo y el vector (delta_x, delta_y). */
	/*Se resta el ángulo absoluto del jugador game->player->angle al ángulo absoluto del rayo.
	 Angle es el ángulo entre el rayo y la dirección de la vista del jugador.*/
	angle = atan2(delta_y, delta_x) - game->player->angle;	
	/*Multiplicar la distancia euclidiana por el coseno del ángulo relativo proyecta esa distancia sobre la dirección de la vista del jugador. */
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}
/*
static void	draw_line(t_player *player, t_data *game, float start_x, int i)
{
    float cos_angle = cos(start_x); //Se calculan segun el angulo del rayo en base a la pos actual
    float sin_angle = sin(start_x);
    float ray_x = player->pos_x;
    float ray_y = player->pos_y;
	float fov_y = FOV * SCREEN_HEIGHT / SCREEN_WIDTH; // Convierte las distancias del campo de vision en base al tamaño de pantalla
	float proj_plane_height = 2 * tan(fov_y / 2); //Distancia del plano de proyeccion
	
    while(!touch(game, ray_y, ray_x))
    {
		//Aqui deberia ir el calculo del DDA. Se calcula la posicion desde donde se lanza el rayo
        ray_x += cos_angle * 0.02; //esto y lo de abajo es lo que se usa para suavizar los bordes/ojo de pez
        ray_y += sin_angle * 0.02;
    }
	//Calcula la distancia perpendicular desde el jugador al rayo. Corrige ojo de pez
	float dist = (fixed_dist(player->pos_x, player->pos_y, ray_x, ray_y, game));
	//Calcula la altura de la columna de la pared segun la distancia (más pequeña o grande) y el plano de vision
	float height = ((1 / dist) / (proj_plane_height) * SCREEN_HEIGHT);

	float start_y = (SCREEN_HEIGHT - height) / 2; //centrar columna
	float end = start_y + height; //chequea que no nos vayamos de mapa
	 
	while(start_y < end) //dibuja paredes
	{
		put_pixel(game, i, start_y, 0xff0000); //Aqui tenemos que poner la asignacion de texutras segun el DDA
		start_y++;
	}
}*/

static void clear_image(t_data *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			put_pixel(game, x, y, 0);
			x += 1;
		}
		y += 1;
	}
    //Normi is not happy with this loop
	//for(int y = 0; y < SCREEN_HEIGHT; y++)
    //    for(int x = 0; x < SCREEN_WIDTH; x++)
    //        put_pixel(game, x, y, 0);
}


int draw_loop(t_data *game)
{
    // t_player *player = game->player;
	
	////Guardamos y modificamos directamente el vector del jugador
	// player->angle += player->angle_flag; //angulo absoluto del jugador o delta de rotacion
    clear_image(game);
	put_floor_ceiling(game);
    //float fraction = FOV / SCREEN_WIDTH; //Calcula el incremento angular para cada rayo (columna).
    //float start_x = player->angle - FOV / 2; //Ángulo del primer rayo (extremo izquierdo del FOV).
    int i = 0;

    while(i < SCREEN_WIDTH)//itera columna por columna pintandolo
    {
		//player->angle_flag = 0; 
        //draw_line(player, game, start_x, i);
		draw_line(game, i); //Dibuja la columna del rayo
        //start_x += fraction; //siguiente rayo ya tu sabe
        i++;
    }
	//mlx_put_image_to_window(game->mlx_ptr, game->w_ptr, game->img_ptr, 0, 0);
	if (game->mlx_ptr == NULL || game->w_ptr == NULL || game->img == NULL)
	{
		error_msg("\nError: Failed to allocate MLX, window or image\n");
		exit (1);
	}
    return 0;
}
