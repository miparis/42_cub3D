/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <saragar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 19:01:37 by miparis           #+#    #+#             */
/*   Updated: 2025/07/15 00:06:32 by saragar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	error_msg(const char *error)
{
	printf(R "%s\n" NC, error);
	return (EXIT_FAILURE);
}

int	go_exit(t_data *data)
{
	free_data(data);
	exit(0);
	return (0);
}
