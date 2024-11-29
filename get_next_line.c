/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichakank <ichakank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:34:43 by ichakank          #+#    #+#             */
/*   Updated: 2024/11/29 17:35:51 by ichakank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *getLine(char *str)
{
    int i;
    int j;
    char *line;
    
    if (!str || !str[0])
        return (NULL);
    i = 0;
    while (str[i] && str[i] != '\n')
        i++;
    line = (char *)malloc(sizeof(char) * (i + 1));
    if (!line)
        return (NULL);
    j = 0;
    while (j <= i)
    {
        line[j] = str[j];
        j++;
    }
    line[j] = '\0';
    return (line);
}

char *clearLine(char *buffer)
{
    int i;
    int j;
    char *newBuffer;

    if (!buffer || !buffer[0])
    {
        free(buffer);
        buffer = NULL;
        return (NULL);
    }
    i = 0;
    while (buffer[i] && buffer[i] != '\n')
    {
        i++;
    }
    newBuffer = malloc(sizeof(char) * (ft_strlen(buffer) - i));
    if (!newBuffer)
    {
        free(buffer);
        return (NULL);
    }
    i++;
    j = 0;
    while (buffer[i])
        newBuffer[j++] = buffer[i++];
    newBuffer[j] = '\0';
    free(buffer);
    return (newBuffer);
}

char *readLine(char *buffer, int fd)
{
    int readBytes;
    char *readBuffer;
    
    readBuffer = malloc(BUFFER_SIZE * sizeof(char) + 1);
    if (!readBuffer)
        return (NULL);
    while ((readBytes = read(fd, readBuffer, BUFFER_SIZE)) > 0)
    {
        // printf("%s\n", readBuffer);
        readBuffer[readBytes] = '\0';
        if (readBytes == -1)
        {
            free(readBuffer);
            return (free(buffer), NULL);
        }
        if (readBytes == 0)
            break;
        if (!buffer)
            buffer = ft_strdup("");
        buffer = ft_strjoin(buffer, readBuffer);
        if (checknewline(buffer))
            break;
    }
    return (buffer);
}
char *get_next_line(int fd)
{
    static char *buffer;
    char *line;
    
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = readLine(buffer, fd);
    line = getLine(buffer);
    buffer = clearLine(buffer);
    return (line);
}
