/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:07:46 by miparis           #+#    #+#             */
/*   Updated: 2024/01/13 18:07:53 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*return_node_content(t_list **list, int bytes)
{
	t_list	*temp;
	char	*content;
	char	*line;

	if (!list || !*list || bytes < 0)
	{
		if (bytes < 0)
		{
			free ((*list)->content);
			free (*list);
			*list = NULL;
		}
		return (NULL);
	}
	temp = (*list)->next;
	content = (*list)->content;
	line = malloc(sizeof(char) * ((*list)->content_size) + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, (*list)->content, (*list)->content_size);
	line[(*list)->content_size] = '\0';
	free (content);
	free (*list);
	*list = temp;
	return (line);
}

t_list	*new_line(t_list **list, char *buffer, size_t start, size_t size)
{
	char	*temp;

	temp = malloc(sizeof(char) * size);
	if (!temp)
		return (NULL);
	ft_memcpy(temp, &buffer[start], size);
	node_addback(list, create_node(temp, size));
	return (iter_last(*list));
}

t_list	*concat_line(t_list *ult_pend, char *buffer, size_t start, size_t size)
{
	char	*temp;
	size_t	content_size;

	content_size = ult_pend->content_size;
	temp = mem_join(ult_pend->content, &buffer[start], content_size, size);
	free(ult_pend->content);
	ult_pend->content = temp;
	ult_pend->content_size = content_size + size;
	return (ult_pend);
}

void	buffer_to_list(char *buffer, size_t size, t_list **list)
{
	size_t	i;
	size_t	line_start;
	t_list	*last;

	i = 0;
	line_start = 0;
	while (i < size)
	{
		if (buffer[i] == '\n' || i == (size - 1))
		{
			last = iter_last(*list);
			if (last && last->pending > 0)
				concat_line(last, buffer, line_start, i - line_start + 1);
			else
				last = new_line(list, buffer, line_start, i - line_start + 1);
			last->pending = !(buffer[i] == '\n');
			line_start = i + 1;
		}
		i++;
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list;
	static int		eof;
	char			*buffer;
	int				bytes;

	bytes = 0;
	while (1)
	{
		if (eof || BUFFER_SIZE <= 0 || fd < 0)
		{
			eof = 0;
			if (list)
				return (return_node_content(&list, bytes));
			return (NULL);
		}
		else if (list && list->pending == 0)
			return (return_node_content(&list, bytes));
		buffer = malloc(sizeof(char) * BUFFER_SIZE);
		if (!buffer)
			return (NULL);
		bytes = read(fd, buffer, BUFFER_SIZE);
		eof = bytes < BUFFER_SIZE;
		buffer_to_list(buffer, bytes, &list);
		free(buffer);
	}
}
