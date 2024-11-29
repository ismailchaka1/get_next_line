/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaka <chaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:34:43 by ichakank          #+#    #+#             */
/*   Updated: 2024/11/30 00:56:15 by chaka            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*extractline(char *str)
{
	int		i;
	int		j;
	char	*line;

	if (!str || !str[0])
	{
		return (NULL);
	}
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = str[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*clearline(char *buffer)
{
	int		i;
	int		j;
	char	*newbuffer;

	if (!buffer || !buffer[0])
		return (free(buffer), NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		i++;
	}
	if (!buffer[i] || !buffer[i + 1])
		return (free(buffer), NULL);
	newbuffer = malloc(sizeof(char) * (ft_strlen(buffer) - i));
	if (!newbuffer)
		return (free(buffer), NULL);
	i++;
	j = 0;
	while (buffer[i])
		newbuffer[j++] = buffer[i++];
	newbuffer[j] = '\0';
	free(buffer);
	return (newbuffer);
}

char	*readline(char *buffer, int fd)
{
	int		readbytes;
	char	*readbuffer;
	char	*temp;

	readbuffer = malloc(BUFFER_SIZE * sizeof(char) + 1);
	if (!readbuffer)
		return (NULL);
	while (1)
	{
		readbytes = read(fd, readbuffer, BUFFER_SIZE);
		if (readbytes == -1)
			return (free(buffer), free(readbuffer), NULL);
		readbuffer[readbytes] = '\0';
		if (readbytes == 0)
			break ;
		if (!buffer)
			buffer = ft_strdup("");
		temp = ft_strjoin(buffer, readbuffer);
		free(buffer);
		buffer = temp;
		if (checknewline(buffer))
			break ;
	}
	free(readbuffer);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	buffer[fd] = readline(buffer[fd], fd);
	line = extractline(buffer[fd]);
	buffer[fd] = clearline(buffer[fd]);
	return (line);
}
