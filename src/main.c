/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:16:16 by miparis           #+#    #+#             */
/*   Updated: 2025/07/12 12:42:36 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_argument	map_arguments; //init & set in general_parse
	t_data		data; // init in set_graphics & set in set_data

	if (argc < 2)
		return (error_msg("\nMissing argument\n"), 1);
	ft_bzero(&map_arguments, sizeof(map_arguments));
	if (general_parse(argv, &map_arguments))
		return (1);
	//print_all(&map_arguments, map_arguments.config);
	if (set_graphics(&data, &map_arguments))
		return (error_msg("\nError setting graphics\n"), 1);
	mlx_put_image_to_window(data.mlx_ptr, data.w_ptr, data.img_ptr, 0, 0);
	mlx_hook(data.w_ptr, 2, 1L << 0, key_control, &data);
	mlx_hook(data.w_ptr, 17, 0, go_exit, &data);
	mlx_loop_hook(data.mlx_ptr, &draw_loop, &data);
	mlx_loop(data.mlx_ptr);
	return (0);
}

//------------------NOTAS
//Para cambiar los bordes, movement.c:99
