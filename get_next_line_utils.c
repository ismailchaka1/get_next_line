/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaka <chaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 15:20:04 by chaka             #+#    #+#             */
/*   Updated: 2024/11/27 16:25:33 by chaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *c)
{
	size_t	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*str;

	i = 0;
	len = ft_strlen(s1);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int checkend(char *str)
{
    int i;

    i = 0;
    if (!str || str[i] == '\0')
        return (0);
    while(str[i])
    {
        if (str[i] == '\n' || str[i] == '\0')
            return (1);
        i++;
    }
    return (0);
}
int	check_node(char *s)
{
	int	i;

	i = 0;
    if (!s)
    {
        return (0);
    }  
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

