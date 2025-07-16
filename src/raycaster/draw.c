/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 23:49:19 by saragar2          #+#    #+#             */
/*   Updated: 2025/07/16 09:54:29 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	draw_line(t_data *game, int start_x)
{
	t_ray	ray_dda;

	ft_bzero(&ray_dda, sizeof(t_ray));
	dda_init(game, start_x, &ray_dda);
	dda_calc(&ray_dda);
	dda_loop(game, &ray_dda);
	ray_dda.line_height = (int)(SCREEN_HEIGHT / ray_dda.perp_wall_dist);
	draw_limits(&ray_dda);
	draw_ray(game, &ray_dda, start_x);
}

void	draw_limits(t_ray *ray)
{
	ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
}

void	draw_ray(t_data *game, t_ray *ray, float start_x)
{
	t_img	*current_tex;

	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			current_tex = &game->textures->ea_tex;
		else
			current_tex = &game->textures->we_tex;
	}
	else
	{
		if (ray->dir_y > 0)
			current_tex = &game->textures->so_tex;
		else
			current_tex = &game->textures->no_tex;
	}
	calc_texture_wall(ray, current_tex->width);
	draw_texture_column(game, ray, start_x, current_tex);
}

void	put_floor_ceiling(t_data *game)
{
	int	y;
	int	x;

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

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= data->img->width || y >= data->img->height)
		return ;
	dst = data->img_data + (y * data->img->line_len + x * (data->img->bpp / 8));
	*(unsigned int *)dst = color;
}
