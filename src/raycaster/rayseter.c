/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayseter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <saragar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:39:03 by miparis           #+#    #+#             */
/*   Updated: 2025/07/08 16:10:46 by saragar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// /*
// y * img->line_len: Te posiciona al inicio de la fila y dentro del buffer.
// Si cada línea ocupa 800 bytes y estás en la fila 3, esto salta 3 * 800 = 2400 bytes.
// x * (img->bpp / 8): Dentro de esa fila, salta x píxeles.
// Como cada píxel ocupa bpp / 8 bytes, multiplicás para moverte horizontalmente.
// Suma total: Obtenés un puntero dst al byte exacto donde está el píxel en (x, y) en la imagen.
// */

void put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

 	if (x < 0)
	{
		error_msg("\nError: Invalid map dimensions x\n");
		return ;
	}
	else if (y < 0)
	{
		error_msg("\nError: Invalid map dimensions y\n");
		return ;
	}
	else if (x >= data->img->width)
	{
		error_msg("\nError: Invalid map dimensions x width\n");
		return ;
	}
	else if (y >= data->img->height)
	{
		error_msg("\nError: Invalid map dimensions y heigth\n");
		return ;
	}
	dst = data->img_data + (y * data->img->line_len + x * (data->img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	set_minimap(t_data *data)
{
	draw_loop(data);
	return (0);
}
