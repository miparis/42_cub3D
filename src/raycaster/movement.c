/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <saragar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:53:49 by saragar2          #+#    #+#             */
/*   Updated: 2025/07/14 20:18:55 by saragar2         ###   ########.fr       */
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
	set_minimap(data);
	return (0);
}

float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(float x1, float y1, float x2, float y2, t_data *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	angle = atan2(delta_y, delta_x) - game->player->angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

void	clear_image(t_data *game)
{
	if (game->img_data)
		ft_bzero(game->img_data, SCREEN_HEIGHT * game->img->line_len);
}

int	draw_loop(t_data *game)
{
	int	i;

	clear_image(game);
	put_floor_ceiling(game);
	i = 0;
	while (i < SCREEN_WIDTH)
	{
		draw_line(game, i);
		i++;
	}
	mlx_put_image_to_window(game->mlx_ptr, game->w_ptr, game->img_ptr, 0, 0);
	if (game->mlx_ptr == NULL || game->w_ptr == NULL || game->img == NULL)
	{
		error_msg("\nError: Failed to allocate MLX, window or image\n");
		exit (1);
	}
	return (0);
}
