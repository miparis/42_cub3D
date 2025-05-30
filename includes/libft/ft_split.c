/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 11:36:08 by miparis           #+#    #+#             */
/*   Updated: 2023/10/11 17:14:42 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_newsubstring(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
		{
			i++;
		}
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != c)
			{
				i++;
			}
		}
	}
	return (count);
}

static size_t	ft_customstrlen(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

static void	ft_free(size_t i, char **array)
{
	while (i > 0)
	{
		i--;
		free(array[i]);
	}
	free (array);
}

static char	**ft_fill(const char *s, char c, char **array, size_t substrings)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < substrings)
	{
		while (s[j] && s[j] == c)
			j++;
		array[i] = ft_substr(s, j, ft_customstrlen((s + j), c));
		if (!array[i])
		{
			ft_free(i, array);
			free_split(array);
			return (NULL);
		}
		while (s[j] && s[j] != c)
			j++;
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	substrings;

	if (!s)
		return (NULL);
	substrings = ft_newsubstring(s, c);
	array = (char **)malloc(sizeof(char *) * (substrings + 1));
	if (!array)
		return (NULL);
	array = ft_fill(s, c, array, substrings);
	return (array);
}
