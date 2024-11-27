/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaka <chaka@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:14:24 by ichakank          #+#    #+#             */
/*   Updated: 2024/11/27 17:05:42 by chaka            ###   ########.fr       */
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
    if (!line)
        return (NULL);
    i = 0;
    // printf(curr->content);
    // printf("%d \n", count);
    while (curr)
    {
        if (!curr->content)
        {
            curr = curr->next;
            continue;
        }
        j = 0;
        while (curr->content[j] && i < count)
        {
            line[i++] = curr->content[j];
            if (curr->content[j] == '\n')
            {
                line[i] = '\0';
                return (line);
            }
            j++;
        }
        curr = curr->next;
    }
    line[i] = '\0'; 
    return (line);
}

int lineCounting(t_list **lst)
{
    t_list *curr;
    int lineCount;
    int i;

    if (!lst || !*lst || !(*lst)->content)
        return (0);

    lineCount = 0;
    curr = *lst;

    while (curr)
    {
        i = 0;
        while (curr->content[i])
        {
            lineCount++;
            if (curr->content[i] == '\n')
                return (lineCount);
            i++;
        }
        curr = curr->next;
    }
    // printf("%d", lineCount);
    return (lineCount);
}



void update_node(t_list **lst)
{
    t_list *curr;
    int i;

    if (!*lst)
        return;

    curr = *lst;
    while (curr)
    {
        if (!curr->content)
        {
            curr = curr->next;
            continue;
        }

        while (curr->content[i])
        {
            if (curr->content[i] == '\n')
            {
                char *new_content = strdup(curr->content + i + 1);
                if (!new_content)
                    return;
                free(curr->content);
                curr->content = new_content;
                break;
            }
            i++;
        }
        curr = curr->next;
    }
}


void clean_node(t_list **lst)
{
    t_list *curr;
    t_list *prev;
    t_list *tmp;

    if (!*lst)
        return;

    curr = *lst;
    prev = NULL;

    while (curr)
    {
        if (!check_node(curr->content))
        { 
            if (prev)
                prev->next = curr->next;
            else
                *lst = curr->next;
            free(curr->content);
            tmp = curr->next;
            free(curr);
            
            curr = tmp;
        }
        else
        {
            update_node(lst);
            break;
        }
    }
}

char *readLine(t_list **lst, int fd)
{
    char *buffer;
    int readBytes;

    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);
    while (1)
    {
        readBytes = read(fd, buffer, BUFFER_SIZE);
        if (readBytes <= 0)
        {
            break;
        }
        buffer[readBytes] = '\0'; 

        ft_lstadd_back(lst, ft_lstnew(strdup(buffer)));
        if (checkend(buffer))
            break;
    }
    // printf("%s", buffer);
    free(buffer);
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
        printf("%s", line);
        if (!line)
            break;
        
        free(line);
    }
    close(fd);
    return 0;
}