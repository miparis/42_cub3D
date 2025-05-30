/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:32:06 by miparis           #+#    #+#             */
/*   Updated: 2024/09/24 12:32:08 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_size(int nbr)
{
	int	n;
	int	len;

	n = nbr;
	len = 0;
	if (nbr <= 0)
		len++;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*put_str(int nbr, int size, char *result)
{
	if (nbr == 0)
	{
		result[0] = '0';
		return (result);
	}
	if (nbr < 0)
	{
		result[0] = '-';
		nbr = -nbr;
	}
	while (nbr)
	{
		size--;
		result[size] = nbr % 10 + '0';
		nbr = nbr / 10;
	}
	return (result);
}

char	*ft_itoa(int nbr)
{
	char	*result;
	int		size;

	if (nbr == -2147483648)
		return ("-2147483648\0");
	size = ft_size(nbr);
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	result[size] = '\0';
	return (put_str(nbr, size, result));
}
