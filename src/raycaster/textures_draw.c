/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 10:48:12 by miparis           #+#    #+#             */
/*   Updated: 2025/07/14 10:26:49 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static unsigned int get_pixel_color(t_img *texture, int x, int y)
{
	char *dst;
	
	//if (x < 0 || x >= texture->width ||   y < 0 || y >= texture->height)
	//	return (0x000000);
	// tex_data->addr es el inicio del buffer.
    // y * tex_data->line_len salta a la fila correcta.
    // x * (tex_data->bpp / 8) salta al píxel correcto dentro de esa fila.
	dst = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
	return (*(unsigned int *)dst);
}
void	calc_texture_wall(t_ray *ray, int current_width)
{
	double wall_x_fractional;

    // Determina cuál coordenada de impacto (X o Y) es relevante y obtiene su parte fraccional
	if (ray->side == 0) // El rayo golpeó una pared vertical (eje X en el mapa)
	{
		wall_x_fractional = ray->wall_hit_y - floor(ray->wall_hit_y);
	}
	else // El rayo golpeó una pared horizontal (eje Y en el mapa)
	{
		wall_x_fractional = ray->wall_hit_x - floor(ray->wall_hit_x);
	}

	// Invierte la coordenada si es necesario, según la dirección del rayo y el lado de la pared.
    // Esta lógica ya la tienes y es correcta para asegurar la orientación de la textura.
	if (ray->side == 0 && ray->dir_x < 0) // Si golpeó una pared Este (rayo va hacia la izquierda)
		wall_x_fractional = 1.0 - wall_x_fractional;
	else if (ray->side == 1 && ray->dir_y > 0) // Si golpeó una pared Norte (rayo va hacia abajo)
		wall_x_fractional = 1.0 - wall_x_fractional;

    // Mapea la coordenada fraccional (0.0 a 1.0) al ancho real de la textura en píxeles.
	ray->wall_x_text = wall_x_fractional * (double)current_width;
}

void	draw_texture_column(t_data *data, t_ray *ray, int x, t_img *texture)
{
	double			step;     // Cuánto avanzar en la coordenada Y de la textura por cada píxel de pantalla
    double			tex_pos;  // Posición flotante actual en la textura (coordenada Y de la textura)
    int   			tex_y;    // Coordenada entera Y del píxel de la textura
    int   			y_pixel;  // Iterador para los píxeles verticales de la pantalla
    unsigned int	color;

	//if (ray->draw_start < 0)
    //	ray->draw_start = 0;
	//if (ray->draw_end >= SCREEN_HEIGHT)
	//	ray->draw_end = SCREEN_HEIGHT - 1;
	step = 1.0 * texture->height / ray->line_height; // Calcular el paso de la textura
	//tex_pos = (ray->draw_start - (SCREEN_HEIGHT / 2 + ray->line_height / 2)) * step;	y_pixel = ray->draw_start;
	tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2 + ray->line_height / 2) * step;
	y_pixel = ray->draw_start;
	while (y_pixel < ray->draw_end)
	{
		tex_y = (int)tex_pos; // Obtener la coordenada Y de la textura
		if (tex_y < 0)
			tex_y = 0; // Asegurarse de que no se salga del rango de la textura
		else if (tex_y >= texture->height)
			tex_y = texture->height - 1; // Asegurarse de que no se salga del rango de la textura
		tex_pos += step; // Avanzar en la textura
		color = get_pixel_color(texture, (int)ray->wall_x_text, tex_y); // Obtener el color del píxel de la textura
		put_pixel(data, x, y_pixel, color); // Dibujar el píxel en la pantalla
		y_pixel++;
	}
}
