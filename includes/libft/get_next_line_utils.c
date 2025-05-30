/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:08:04 by miparis           #+#    #+#             */
/*   Updated: 2024/01/13 18:08:06 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*create_node(char *read_content, size_t size)
{
	t_list	*node;

	if (size <= 0)
		return (NULL);
	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = read_content;
	node->content_size = size;
	node->next = NULL;
	return (node);
}

t_list	*iter_last(t_list *list)
{
	while (list && list -> next)
		list = list -> next;
	return (list);
}

t_list	*node_addback(t_list **list, t_list *new)
{
	t_list	*n;

	if (!list)
		return (NULL);
	if (!*list)
		*list = new;
	else
	{
		n = iter_last(*list);
		n -> next = new;
	}
	return (new);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*srccpy;
	unsigned char	*destcpy;

	i = 0;
	if (!src)
		return (NULL);
	srccpy = (unsigned char *)src;
	destcpy = (unsigned char *)dst;
	while (n > i)
	{
		destcpy[i] = srccpy[i];
		i++;
	}
	return (dst);
}

char	*mem_join(char *s1, char *s2, size_t l1, size_t l2)
{
	char	*mem;

	if (!s1 || !s2)
		return (NULL);
	mem = malloc(l1 + l2);
	if (!mem)
		return (NULL);
	ft_memcpy(mem, s1, l1);
	ft_memcpy(mem + l1, s2, l2);
	return (mem);
}
