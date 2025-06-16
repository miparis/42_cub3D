/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:16:16 by miparis           #+#    #+#             */
/*   Updated: 2025/06/16 16:02:26 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int argc, char **argv)
{
	t_argument	map_arguments;

	ft_bzero(&map_arguments, sizeof(map_arguments));
	if (general_parse(argc, argv, map_arguments))
		return (1);
	//free_all(&map_arguments, NULL);
	printf("MIAU MIAU\n");
	return (0);
}