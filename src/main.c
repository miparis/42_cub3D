/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:16:16 by miparis           #+#    #+#             */
/*   Updated: 2025/07/03 11:23:10 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int go_exit(t_data *data)
{
	free_data(data);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_argument	map_arguments; //init & set in general_parse
	t_data		data; // init in set_graphics & set in set_data

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

//----------NOTAS----------
//de vez en cuando por la cara da deadlysig
//el unico mapa que se ve correctamente es el HIGH. los demas se ven estirados