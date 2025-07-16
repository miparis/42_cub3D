/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 18:53:49 by saragar2          #+#    #+#             */
/*   Updated: 2025/07/16 09:57:17 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	clear_image(t_data *game)
{
	if (game->img_data)
		ft_bzero(game->img_data, SCREEN_HEIGHT * game->img->line_len);
}

int	game_loop(t_data *game)
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
