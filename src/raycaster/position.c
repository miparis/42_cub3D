/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   position.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 20:19:11 by saragar2          #+#    #+#             */
/*   Updated: 2025/07/16 09:57:26 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	key_control(int keycode, t_data *data)
{
	if (keycode == 65307)
		go_exit(data);
	else if (keycode == 119)
		update_position(data, cos(data->player->angle) * M_SPEED,
			sin(data->player->angle) * M_SPEED);
	else if (keycode == 115)
		update_position(data, cos(data->player->angle) * -M_SPEED,
			sin(data->player->angle) * -M_SPEED);
	else if (keycode == 100)
		update_position(data, sin(data->player->angle) * -M_SPEED,
			cos(data->player->angle) * M_SPEED);
	else if (keycode == 97)
		update_position(data, sin(data->player->angle) * M_SPEED,
			cos(data->player->angle) * -M_SPEED);
	if (keycode == 65361)
		rotate_camera(data, 65361);
	if (keycode == 65363)
		rotate_camera(data, 65363);
	mlx_put_image_to_window(data->mlx_ptr, data->w_ptr, data->img_ptr, 0, 0);
	return (0);
}

int	update_position(t_data *data, double x, double y)
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

void	rotate_camera(t_data *data, int keycode)
{
	double	old_dir_x;
	double	old_plane_x;
	double	r_speed;

	r_speed = 0;
	if (keycode == 65363)
		r_speed = R_SPEED;
	else if (keycode == 65361)
		r_speed = -R_SPEED;
	old_dir_x = data->player->dir_x;
	old_plane_x = data->player->plane_x;
	data->player->dir_x = old_dir_x * cos(r_speed)
		- data->player->dir_y * sin(r_speed);
	data->player->dir_y = old_dir_x * sin(r_speed)
		+ data->player->dir_y * cos(r_speed);
	data->player->plane_x = old_plane_x * cos(r_speed)
		- data->player->plane_y * sin(r_speed);
	data->player->plane_y = old_plane_x * sin(r_speed)
		+ data->player->plane_y * cos(r_speed);
	data->player->angle += r_speed;
}

int	touch(t_data *data, int px_map_y, int py_map_x)
{
	if (px_map_y < 0 || px_map_y >= (int)data->map->height)
	{
		error_msg("\nError: Collision detected");
		printf("px_map_y: %i\n", px_map_y);
		return (1);
	}
	if (py_map_x < 0 || py_map_x >= (int)ft_strlen(data->map->map[px_map_y]))
		return (1);
	if (data->map->map[px_map_y][py_map_x] == '1')
		return (1);
	return (0);
}
