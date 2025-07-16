/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DDA.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:04:26 by miparis           #+#    #+#             */
/*   Updated: 2025/07/16 09:54:17 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	dda_init(t_data *data, int screen_x, t_ray *ray)
{
	double	camera_x;

	camera_x = (2 * screen_x / (double)SCREEN_WIDTH) - 1;
	ray->pos_x = data->player->pos_x;
	ray->pos_y = data->player->pos_y;
	ray->dir_x = data->player->dir_x + data->player->plane_x * camera_x;
	ray->dir_y = data->player->dir_y + data->player->plane_y * camera_x;
	ray->map_x = (int)ray->pos_x;
	ray->map_y = (int)ray->pos_y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = false;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
}

void	dda_calc(t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
	}
}

void	dda_loop(t_data *data, t_ray *ray)
{
	while (!ray->hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (touch(data, ray->map_y, ray->map_x))
			ray->hit = true;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else if (ray->side == 1)
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->wall_hit_x = ray->pos_x + ray->dir_x * ray->perp_wall_dist;
	ray->wall_hit_y = ray->pos_y + ray->dir_y * ray->perp_wall_dist;
}
