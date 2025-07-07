/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <saragar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:08:27 by miparis           #+#    #+#             */
/*   Updated: 2025/07/07 15:06:16 by saragar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	set_position(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < data->map->height)
	{
		j = 0;
		while (j < data->map->width)
		{
			if (ft_strchr("NSEW", data->map->map[i][j]))
			{
				data->player->pos_x = (double)j + 0.5;
				data->player->pos_y = (double)i + 0.5;
				data->map->map[i][j] = '0';
				return (0);
			}
			j++;
		}
		i++;
	}
	return (error_msg("\nError: Player not found in map\n"), 1);
}

static void	set_dir(double dir_x, double dir_y, t_player *player)
{
	player->dir_x = dir_x;
	player->dir_y = dir_y;
}

static void	set_plane(double plane_x, double plane_y, t_player *player)
{
	player->plane_x = plane_x;
	player->plane_y = plane_y;
}

int	set_orientation(t_data *data)
{
	if (data->map->orientation == 'N')
	{
		set_dir(0.0, -1.0, data->player);
		data->player->angle = 3 * M_PI / 2; // Set the angle to 90 degrees for North orientation
		return (set_plane(FOV, 0.0, data->player), 0);
	}
	else if (data->map->orientation == 'S')
	{
		set_dir(0.0, 1.0, data->player);
		data->player->angle = M_PI / 2; // Set the angle to 180 degrees for South orientation
		return (set_plane(-FOV, 0.0, data->player), 0);
	}
	else if (data->map->orientation == 'E')
	{
		set_dir(1.0, 0.0, data->player);
		data->player->angle = 0; // Set the angle to 0 degrees for East orientation	
		return (set_plane(0.0, FOV, data->player), 0);
	}
	else if (data->map->orientation == 'W')
	{
		set_dir(-1.0, 0.0, data->player);
		data->player->angle = M_PI; // Set the angle to 180 degrees for West orientation
		return (set_plane(0.0, -FOV, data->player), 0);
	}
	else
		return (error_msg("\nError: Problem assigning FOV & direction\n"), 1);
}
