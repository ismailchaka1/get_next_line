/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ichakank <ichakank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:14:24 by ichakank          #+#    #+#             */
/*   Updated: 2024/11/24 16:21:06 by ichakank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <string.h>


static t_list	*ft_lstnew(void *content)
{
	t_list	*head;

	head = (t_list *)malloc(sizeof(t_list));
	if (!head)
		return (NULL);
	head->content = content;
	head->next = NULL;
	return (head);
}

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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	lenn;
	char			*str;
	unsigned int	i;

	if (!s)
		return (NULL);
	lenn = strlen(s);
	if (len == 0 || start >= lenn)
		return (calloc(1, sizeof(char)));
	if (start + len > lenn)
		len = lenn - start;
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[i + start];
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
        if (str[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
	{
		lst = lst->next;
	}
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}

int	ft_lstsize(t_list *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

void	ft_lstclear(t_list **lst)
{
    t_list	*current;
    t_list	*next_node;
    char	*newline_pos;
    int     i = 0;
    char *restline;
    if (!lst || !*lst)
        return;
    current = *lst;
    while (current->next != NULL)
    {
        
        next_node = current->next;
        free(current->content); 
        current->content = NULL;
        free(current);
        current = next_node;
    }
    while (current->content[i] != '\n' && current->content[i++] != '\0');
    
    if (current->content[i] == '\n')
        i++;
    restline = ft_strdup(current->content + i);
    free(current->content);
    free(current);
    *lst = NULL;
    ft_lstadd_back(lst, ft_lstnew(restline));
    printf("%d\n", ft_lstsize(*lst));
}


char *extractLine(t_list **lst, int fd)
{
    t_list *current;
    char *line = NULL;
    int i = 0;
    char *buffer = (char *)malloc(BUFFER_SIZE + 1);
    int readedBytes;

    if (!buffer)
        return (NULL);
    while ((readedBytes = read(fd, buffer, BUFFER_SIZE)) > 0)
    {
        buffer[readedBytes] = '\0'; 
        ft_lstadd_back(lst, ft_lstnew(ft_strdup(buffer)));
        if (checkend(buffer))
            break;
    }
    
    if (readedBytes < 0)
    {
        free(buffer);
        return (NULL);
    }

    current = *lst;
    int lineCount = 0;
    while (current)
    {
        i = 0;
        while (current->content[i])
        {
            if (current->content[i++] != '\n')
                lineCount++;
            else
                break;
        }
        current = current->next;
    } 
    
    line = (char *)malloc(lineCount + 1);  
    if (!line)
    {
        free(buffer);
        return (NULL);
    }

    int j = 0;
    current = *lst;
    while (current)
    {
        i = 0;
        while (current->content[i])
        {
            if (current->content[i] == '\n')  
            {
                line[j] = '\0';
                free(buffer);
                ft_lstclear(lst);
                return (line);
            }
            line[j++] = current->content[i++];
            
        }
        // free(current->content);
        current = current->next;
    }
    current = *lst;
    // t_list *next_node;
    // while (current)
    // {
    //     next_node = current->next;
    //     // if (checkend(current->content))  
    //     // {
    //         current->content = NULL;
    //         free(current->content);
    //         free(current);
    //     // }

    //     current = next_node;
    // }
    // *lst = next_node;    
    // printf("%d\n", ft_lstsize(*lst));
    free(buffer);
    return (line);
}


static int	is_trim(char s, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (s == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i] && is_trim(s1[i], (char *)set))
		i++;
	while (s1[j] && is_trim(s1[j], (char *)set))
		j--;
	str = ft_substr(s1, i, (j - i + 1));
	return (str);
}

// void ft_clean(t_list **lst)
// {
//     t_list *current;
//     t_list *next_node;
//     t_list *prev = NULL;
//     int i = 0;
//     current = *lst;
//     while (current)
//     {
//         next_node = current->next;
//         i = 0;
//         while (current->content[i])
//         {
//             if (current->content[i] == '\n')
//             {
//                 // if (prev)
//                 //     prev->next = next_node;
//                 // else
//                 ft_substr(current->content, i, strlen(current->content) - i);
//                 *lst = next_node;
                
//                 // free(current->content);
//                 // free(current);
//                 break;
//             }
//             i++;
//         }
//         current = next_node;
//     }
// }

char *get_next_line(int fd)
{
    if (fd < 0 || BUFFER_SIZE < 0)
        return (NULL);
    static t_list *lst;
    // t_list *current, *new_node;
    // buffer = malloc(BUFFER_SIZE + 1);
    // if (!buffer)
    //     return (NULL);
    // int readedBytes = read(fd, buffer, BUFFER_SIZE);
    // if (readedBytes < 0)
    // {
    //     free(buffer);
    //     return (NULL);
    // }
    // new_node = ft_lstnew(buffer);
    // if (!lst)
    //     lst = new_node;
    // else
    // {
    //     current = lst;
    //     while (current->next)
    //         current = current->next;
    //     current->next = new_node;
    // }
    // printf("dsasdasdasd \n");
    char *line = extractLine(&lst,fd);
    // ft_clean(&lst);
    
    return(line);
}


int main()
{
    int  fd = open("test.txt", O_RDONLY);
    // get_next_line(fd);
    // get_next_line(fd);
    char *line = get_next_line(fd);
    printf("%s\n", line);
    free(line);
    char *line2 = get_next_line(fd);
    printf("%s\n", line2);
    free(line2);
    char *line3 = get_next_line(fd);
    printf("%s\n", line3);
    free(line3);
    return 0;
}   