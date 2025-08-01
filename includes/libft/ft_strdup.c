/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miparis <miparis@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 17:48:12 by miparis           #+#    #+#             */
/*   Updated: 2025/06/05 17:48:46 by miparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s)
{
	char	*new;
	int		i;

	i = 0;
	while (s[i])
		i++;
	new = malloc (i + 1);
	if (!new)
		return (NULL);
	while (i >= 0)
	{
		new[i] = s[i];
		i--;
	}
	return (new);
}

/*int	main(void)
{
	const char *original = "Hello, world!";
    char *ft_result = ft_strdup(original);

    if (ft_result == NULL) {
        printf("Error: ft_strdup failed.\n");
        return 1;
    }

    printf("Resultado de ft_strdup: %s\n", ft_result);

    char *std_result = strdup(original);

    if (std_result == NULL) {
        printf("Error: strdup failed.\n");
        return 1;
    }

    printf("Resultado de strdup: %s\n", std_result);

    // Liberar memoria asignada
    free(ft_result);
    free(std_result);

    return (0);
}*/
