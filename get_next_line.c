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
char *extractLine(t_list **lst, int count)
{
    char *line;
    t_list *curr;
    int i;
    int j;

    if (!*lst)
        return (NULL);
    curr = *lst;
    line = malloc(count + 1);
    i = 0;
    j = 0;
    if (!line)
        return (NULL);
    if (!curr->content)
        return (NULL);
    line[count] = '\0';
	while (curr)
	{
		j = 0;
		while (curr->content[j])
		{
			line[i++] = curr->content[j++];
			if (curr->content[j - 1] == '\n')
				return (line);
		}
		curr = curr->next;
	}
    // printf("line: %s\n", line);
    return (line);
}

int lineCounting(t_list **lst)
{
    t_list *curr;
    int lineCount;
    int i;

    lineCount = 0;
    curr = *lst;
    if (!*lst)
        return (0);
    if (!curr->content)
        return (0);
    // printf("content: %s\n", curr->content);
    while (curr)
    {
        i = 0;
        while (curr->content[i])
        {
            if (curr->content[i] != '\n')
                lineCount++;
            i++;
        }
        curr = curr->next;
    }
    return (lineCount);
}

int	check_node(char *s)
{
	int	i;

	i = 0;
    if (!s)
        return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void update_node(t_list **lst)
{
    t_list *curr;
    int i;

    curr = *lst;
    if ( !lst || !*lst)
        return;
    printf("content: %s\n", curr->content);
    while (curr )
    {
        i = 0;
        while (curr->content && curr->content[i])
        {
            if (curr->content[i] == '\n')
            {
                
                char *new_content = strdup(curr->content + i + 1);
                if (!new_content)
                    return;
                free(curr->content);
                curr->content = new_content;
                return;
            }
            i++;
        }
        curr = curr->next;
        
    }

}


void	clean_node(t_list **lst)
{
	t_list	*curr;
    t_list	*tmp;

    curr = *lst;
	while (curr)
	{
        printf("content 111: %s\n", curr->content);
		if (!check_node(curr->content))
		{
            curr->content = NULL;
			free(curr->content);
			tmp = curr->next;
            curr->next = NULL;
			free(curr);
		}
		else
		{
            printf("content 222: %s\n", curr->content);
            update_node(lst);
            break;
		}
        curr = tmp;
	}
    *lst = curr;
}

char *readLine(t_list **lst, int fd)
{
    char *buffer;
    int readBytes;

    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);
    while (*lst == NULL || !check_node((*lst)->content))
    {
        readBytes = read(fd, buffer, BUFFER_SIZE);
        if (readBytes <= 0)
        {
            // free(buffer);
            break;
        }
        buffer[readBytes] = '\0'; 

        ft_lstadd_back(lst, ft_lstnew(strdup(buffer)));
        if (checkend(buffer))
            break;
    }
    free(buffer);
    // printf("lineCount: %d\n", ft_lstsize(*lst));
    return (extractLine(lst, lineCounting(lst)));
}

char *get_next_line(int fd)
{
    static t_list *lst;
    char *line = readLine(&lst, fd);
    clean_node(&lst);
    return (line);
}
int main()
{
    int fd = open("test.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (1);
    }

    while (1)
    {
        char *line = get_next_line(fd);
        if (!line)
            break;
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}