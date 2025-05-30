/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 17:12:43 by miparis           #+#    #+#             */
/*   Updated: 2024/07/02 11:30:55 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_list
{
	char			*content;
	size_t			content_size;
	int				pending;
	struct s_list	*next;
}					t_list;

char	**ft_split(char const *s, char c);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	free_split(char **array_split);
void	free_list(t_list **list);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_itoa(int nbr);

/*                     GNL					                                  */
/*                     Principal Functions                                  */
char	*get_next_line(int fd);
void	buffer_to_list(char *buffer, size_t size, t_list **list);
t_list	*new_line(t_list **list, char *buffer, size_t start, size_t size);
t_list	*concat_line(t_list *ult_pend, char *buffer, size_t start, size_t size);
char	*return_node_content(t_list **list, int bytes);

/*                     List operations                                       */
t_list	*create_node(char *read_content, size_t size);
t_list	*iter_last(t_list *list);
t_list	*node_addback(t_list **list, t_list *new);

/*                     Memory and buffer operations                          */
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*mem_join(char *s1, char *s2, size_t l1, size_t l2);

#endif
