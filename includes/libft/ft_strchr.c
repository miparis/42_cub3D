/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 09:45:32 by miparis           #+#    #+#             */
/*   Updated: 2023/09/29 10:26:49 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			len;
	size_t			i;
	unsigned char	d;

	d = (unsigned char) c;
	len = ft_strlen(s);
	i = 0;
	while ((i <= len))
	{
		if (s[i] == d)
			return ((char *) &s[i]);
		i++;
	}
	return (0);
}
