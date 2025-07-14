/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_values.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saragar2 <saragar2@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:35:59 by miparis           #+#    #+#             */
/*   Updated: 2025/07/14 18:37:19 by saragar2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	copy_path(char *line, char **text_path, bool *flag)
{
	char	*path_start;
	char	*trimmed;

	path_start = NULL;
	trimmed = NULL;
	trimmed = ft_strtrim(line, "\n");
	path_start = trimmed + 2;
	while (path_start && ft_isspace(*path_start))
		path_start++;
	if (flag && *flag)
	{
		free(trimmed);
		return (error_msg("\nError: Duplicate texture identifier\n"), 1);
	}
	*text_path = ft_strdup(path_start);
	free(trimmed);
	if (open(*text_path, O_RDONLY) < 0)
	{
		free(*text_path);
		*text_path = NULL;
		return (error_msg("\nError: Invalid path for file texture\n"), 1);
	}
	*flag = true;
	return (0);
}

static char	*remove_spaces_around_commas(char *str)
{
	char	*result;
	int		j;
	int		i;

	i = 0;
	j = 0;
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == ' ' && (str[i + 1] == ','
				|| (i > 0 && str[i - 1] == ',')))
			i++;
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

int	parse_color(char *line, int *color_dest, bool *flag)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;
	char	*clean;

	if (*flag)
		return (error_msg("\nError: Duplicate color identifier\n"), 1);
	line += 1;
	while (*line && ft_isspace(*line))
		line++;
	clean = remove_spaces_around_commas(line);
	if (!clean)
		return (error_msg("\nError: Memory allocation failed\n"), 1);
	rgb = ft_split(clean, ',');
	free(clean);
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		return (free_split(rgb), error_msg("\nError: Invalid RGB format\n"), 1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (free_split(rgb), error_msg("\nError: RGB out of range\n"), 1);
	*color_dest = (r << 16) | (g << 8) | b;
	return ((*flag = true), free_split(rgb), 0);
}
