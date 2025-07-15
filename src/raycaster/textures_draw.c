/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_draw.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <saragar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 10:48:12 by miparis           #+#    #+#             */
/*   Updated: 2025/07/14 19:54:18 by saragar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static unsigned int	get_pixel_color(t_img *texture, int x, int y)
{
	char	*dst;

	dst = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
	return (*(unsigned int *)dst);
}

void	calc_texture_wall(t_ray *ray, int current_width)
{
	double	wall_x_fractional;

	if (ray->side == 0)
	{
		wall_x_fractional = ray->wall_hit_y - floor(ray->wall_hit_y);
	}
	else
	{
		wall_x_fractional = ray->wall_hit_x - floor(ray->wall_hit_x);
	}
	if (ray->side == 0 && ray->dir_x < 0)
		wall_x_fractional = 1.0 - wall_x_fractional;
	else if (ray->side == 1 && ray->dir_y > 0)
		wall_x_fractional = 1.0 - wall_x_fractional;
	ray->wall_x_text = wall_x_fractional * (double)current_width;
}

void	draw_texture_column(t_data *data, t_ray *ray, int x, t_img *texture)
{
	double			step;
	double			tex_pos;
	int				tex_y;
	int				y_pixel;
	unsigned int	color;

	step = 1.0 * texture->height / ray->line_height;
	tex_pos = (ray->draw_start - SCREEN_HEIGHT / 2
			+ ray->line_height / 2) * step;
	y_pixel = ray->draw_start;
	while (y_pixel < ray->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= texture->height)
			tex_y = texture->height - 1;
		tex_pos += step;
		color = get_pixel_color(texture, (int)ray->wall_x_text, tex_y);
		put_pixel(data, x, y_pixel, color);
		y_pixel++;
	}
}
