/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madridcom>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:34:53 by miparis           #+#    #+#             */
/*   Updated: 2023/10/10 17:15:23 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	error(void)
{
	write(1, "Error\n", 6);
	exit (1);
}

static int	ft_isspace(int c)
{
	if ((c == ' ' || c == '\t' || c == '\v' || \
		c == '\n' || c == '\f' || c == '\r' ))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	i;
	int	sign;
	int	digit;

	result = 0;
	i = 0;
	sign = 1;
	while (ft_isspace(str[i]) && str[i] != '\0')
		i++;
	if ((str[i] == '-') || (str[i] == '+'))
	{
		sign = 1 - 2 * (str[i] == '-');
		i++;
	}
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		digit = str[i] - '0';
		if (result > (INT_MAX - digit) / 10)
			error();
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (sign * result);
}
