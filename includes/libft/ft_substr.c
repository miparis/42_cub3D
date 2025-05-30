/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 15:22:17 by miparis           #+#    #+#             */
/*   Updated: 2023/10/10 17:16:09 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	lenght;
	size_t	len_substr;
	char	*substr;

	if (!s)
		return (NULL);
	lenght = ft_strlen(s) + 1;
	if ((start >= lenght) || (len == 0))
		len_substr = 1;
	else if (len >= lenght - start)
		len_substr = lenght - start;
	else
		len_substr = len + 1;
	substr = malloc(sizeof(char) * (len_substr));
	if (substr == NULL)
		return (NULL);
	if (lenght > start)
		ft_strlcpy(substr, s + start, len_substr);
	else
		substr[0] = '\0';
	return (substr);
}
