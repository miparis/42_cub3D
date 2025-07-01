/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <saragar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:16:16 by miparis           #+#    #+#             */
/*   Updated: 2025/07/01 21:02:47 by saragar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int go_exit(t_data *data)
{
	free_data(data);
	exit(0);
	return (0);
}

int	key_control(int keycode, t_data *data)
{
	int	row;
	int	col;

	row = (int)data->player->pos_y;
	col = (int)data->player->pos_x;
	if (keycode == 65307) //if "ESC" is pressed, the program closes in a clean way
		go_exit(data);
	// if (keycode == 65361 || keycode == 65362 || keycode == 65363 || keycode == 65364
	// || keycode == 65451 || keycode == 65453) //if any arrow or the "+" or "-" are pressed, we enter
	// //to move_left_right, in image.c
	if (keycode == 97 && !touch(data, row, col - 1))
		data->player->pos_x -= 1;
	if (keycode == 119 && !touch(data, row - 1, col))
		data->player->pos_y -= 1;
	if (keycode == 100 && !touch(data, row, col + 1))
		data->player->pos_x += 1;
	if (keycode == 115 && !touch(data, row + 1, col))
		data->player->pos_y += 1;
	set_minimap(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_argument	map_arguments;
	t_data		data;

	if (argc < 2)
		return (error_msg("\nMissing argument\n"), 1);
	ft_bzero(&map_arguments, sizeof(map_arguments));
	if (general_parse(argv, &map_arguments))
		return (1);
	print_all(&map_arguments, map_arguments.config);
	if (set_graphics(&data, &map_arguments))
		return (error_msg("\nError setting graphics\n"), 1);
	//free_all(&map_arguments, NULL);

	mlx_hook(data.w_ptr, 2, 1L << 0, key_control, &data);
	mlx_hook(data.w_ptr, 17, 0, go_exit, &data);
	mlx_loop(data.mlx_ptr);
	printf("MIAU MIAU\n");
	return (0);
}