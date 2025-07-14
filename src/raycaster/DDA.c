/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:04:26 by miparis           #+#    #+#             */
/*   Updated: 2025/07/14 11:14:09 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
ray->dir_x y ray->dir_y: Son los componentes X e Y del vector de dirección del rayo. Este vector tiene una longitud arbitraria (no tiene por qué ser unitario para el DDA, aunque a menudo lo es).

fabs(1 / ray->dir_x) y fabs(1 / ray->dir_y):

Imagina que tienes un rayo. Queremos saber cuánto tiene que avanzar ese rayo para que su componente X (o Y) cambie exactamente en 1 unidad.

Si ray->dir_x es, por ejemplo, 0.5 (es decir, por cada unidad que el rayo avanza en su dirección, se mueve 0.5 unidades en X), entonces para mover 1 unidad en X, el rayo necesita avanzar 1 / 0.5 = 2 unidades en su dirección.

Si ray->dir_x es 2.0 (por cada unidad que el rayo avanza en su dirección, se mueve 2.0 unidades en X), entonces para mover 1 unidad en X, el rayo necesita avanzar 1 / 2.0 = 0.5 unidades en su dirección.

fabs() (valor absoluto) se usa porque la distancia siempre es positiva, sin importar si ray->dir_x es positivo o negativo.

Propósito en el DDA: delta_dist_x y delta_dist_y nos dicen cuánto "cuesta" en términos de "longitud de rayo" cruzar una unidad completa de cuadrícula en el eje X o Y, respectivamente. Esto permite al DDA decidir eficientemente si el rayo golpeará una línea vertical o una horizontal primero.

Manejo del Caso ray->dir_x == 0 (Rayos Perfectamente Horizontales/Verticales)
Si ray->dir_x es 0, significa que el rayo es perfectamente vertical (no tiene componente de movimiento en X). Dividir por cero (1 / 0) causaría un error en tiempo de ejecución.

En este caso, el rayo nunca cruzará una línea vertical (un cambio en X) a menos que cambie su dirección. Por lo tanto, la "distancia para cruzar una unidad en X" es efectivamente infinita.

El valor 1e30 (que es 1 * 10^30, un número muy grande) simula este "infinito". Al ser un número tan grande, cuando se compara con side_dist_y en el bucle DDA (if (side_dist_x < side_dist_y)), siempre será mayor, forzando al rayo a avanzar en la dirección Y hasta que golpee algo.

*/

static void	dda_init(t_data *data, int screen_x, t_ray *ray)
{
	double	camera_x;

	 // Calcula la coordenada X de la cámara
	camera_x = (2 * screen_x / (double)SCREEN_WIDTH) - 1;
	ray->pos_x = data->player->pos_x;
	ray->pos_y = data->player->pos_y;

	//Vectores de direccion del rayo
	ray->dir_x = data->player->dir_x + data->player->plane_x * camera_x;
	ray->dir_y = data->player->dir_y + data->player->plane_y * camera_x;
	//ray->side_dist_x = 0; //ver si init aqui para evitar problemas
	//ray->side_dist_y = 0;// init aqui
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;

	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30; // Evita división por cero
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30; // Evita división por cero
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = false;
	//ray->side = 0;
	//ray->perp_wall_dist = 0;
	//ray->wall_hit_x = 0;
	//ray->wall_hit_y = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}


//Calcula las distancias del rayo a cada borde de posible direccion segun la celda
static void	dda_calc(t_ray *ray)
{
	if (ray->dir_x < 0) //X negativo == izquierda
	{
		ray->step_x = -1;
		// Distancia al borde izquierdo de la celda actual
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else //X positivo == derecha
	{
		ray->step_x = 1;
		// Distancia al borde derecho de la celda actual
		ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)// Y negativo == arriba
	{
		ray->step_y = -1;
		// Distancia al borde superior de la celda actual
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else //Y positivo == abajo
	{
		ray->step_y = 1;
		// Distancia al borde inferior de la celda actual
		ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
	}
}

static void dda_loop(t_data *data, t_ray *ray)
{
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y) //chequeo vertical
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0; // 0 indica que el rayo ha tocado una pared vertical
		}
		else //chequeo horizontal
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1; // 1 indica que el rayo ha tocado una pared horizontal
		}
		if (touch(data, ray->map_y, ray->map_x)) //chequea si ha tocado una pared
			ray->hit = true;
	}
	//distancias de impacto
	if (ray->side == 0)
			ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else if (ray->side == 1)
			ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	//punto de impacto para texturizar
	//punto_impacto = pos_inicial + dir_rayo * distancia_al_impacto
	ray->wall_hit_x = ray->pos_x + ray->dir_x * ray->perp_wall_dist;
	ray->wall_hit_y = ray->pos_y + ray->dir_y * ray->perp_wall_dist;
}

static void draw_limits(t_ray *ray)
{
	ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0; // Asegura que no dibuje por encima de la pantalla
	ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1; // Asegura que no dibuje por debajo de la pantalla
}

static void	draw_ray(t_data *game, t_ray *ray, float start_x)
{
	//int		y_pix;
	//int		wall_def;//podemos cambiar para poner text
	t_img	*current_texture;

	if (ray->side == 0)
	{
		if (ray->dir_x > 0) //lado este
		{
			current_texture = &game->textures->ea_texture; //textura este
			//wall_def = 0x0000FF; // Azul para Este
		}
		else //lado oeste
        {
			current_texture = &game->textures->we_texture; //textura este
			//wall_def = 0x00FF00; // Verde para Oeste
		}
	}
	else // Lado Y (horizontal en el mapa, rayo golpeó un eje X)
    {
        if (ray->dir_y > 0) //Sur
        {
			current_texture = &game->textures->so_texture; //textura este
			//wall_def = 0xFFFF00; // Amarillo para Sur
		}
		else // Rayo va hacia arriba, golpeó lado Norte
        {
			current_texture = &game->textures->no_texture; //textura este
			//wall_def = 0xFF0000; // Rojo para Norte
		}
    }
	calc_texture_wall(ray, current_texture->width); //calcula coordenada de textura
	draw_texture_column(game, ray, start_x, current_texture); //dibuja la columna de textura
	/*
	y_pix = ray->draw_start;
	while (y_pix <= ray->draw_end)
	{
		//aqui poner textura
		put_pixel(game, start_x, y_pix, wall_def); // Dibuja el pixel con el color de la pared
		y_pix++;
	}*/
}

void put_floor_ceiling(t_data *game)
{
	int y;
	int x;

	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			put_pixel(game, x, y, game->config->ceiling_color);
			x++;
		}
		y++;
	}
	y = SCREEN_HEIGHT / 2;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			put_pixel(game, x, y, game->config->floor_color);
			x++;
		}
		y++;
	}
}

void	draw_line(t_data *game, int start_x)
{
  t_ray ray_dda;

  ft_bzero(&ray_dda, sizeof(t_ray));
  dda_init(game, start_x, &ray_dda);
  dda_calc(&ray_dda);
  dda_loop(game, &ray_dda);
  ray_dda.line_height = (int)(SCREEN_HEIGHT / ray_dda.perp_wall_dist);
  draw_limits(&ray_dda);
  draw_ray(game, &ray_dda, start_x);
}




