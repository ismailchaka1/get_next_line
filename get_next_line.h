/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichakank <ichakank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:15:18 by ichakank          #+#    #+#             */
/*   Updated: 2024/11/28 20:05:51 by ichakank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;
#ifndef BUFFER_SIZE
    #define BUFFER_SIZE 1
#endif
size_t	ft_strlen(const char *c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);
int checknewline(char *str);
char *get_next_line(int fd);

#endif
