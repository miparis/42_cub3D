/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_subarray.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:44:00 by miparis           #+#    #+#             */
/*   Updated: 2024/05/31 10:44:01 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_split(char **array_split)
{
	int	i;

	if (!array_split)
		return ;
	i = 0;
	while (array_split[i])
	{
		free(array_split[i]);
		i++;
	}
	free(array_split);
}

void	free_list(t_list **list)
{
	t_list	*temp;

	while (*list)
	{
		temp = ((*list)->next);
		free((*list)->content);
		free(*list);
		*list = temp;
	}
}
