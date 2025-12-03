/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounoua <abounoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:13:10 by abounoua          #+#    #+#             */
/*   Updated: 2025/12/03 18:04:24 by abounoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_to_newline(char *str)
{
	size_t	len;
	
	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	len += str[len] == '\n';
	return (len);
}

size_t	contains_newline(t_list *lst_last)
{
	size_t	i;

	if (!lst_last)
		return (0);
	i = 0;
	while ((lst_last->data)[i])
	{
		if ((lst_last->data)[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	*free_everything(t_list *lst)
{
	t_list	*node;
	t_list	*temp;

	node = lst;
	while (node)
	{
		temp = node->next;
		free(node->data);
		free(node);
		node = temp;
	}
	return (NULL);
}

t_list	*push_stash(const char *s, t_list **lst, t_list **lst_last)
{
	size_t  len;
    char    *dup;
	t_list	*stash;

	len = 0;
	while (s[len])
        len++;
    dup = malloc(sizeof(char) * (len + 1));
    if (!dup)
        return (NULL);
    len = 0;
    while (s[len])
	{
        dup[len] = s[len];
		len++;
	}
    dup[len] = '\0';
    stash = malloc(sizeof(t_list));
	if (!stash)
	{
		free(dup);
		return (NULL);
	}
	stash->data = dup;
	*lst = stash;
	*lst_last = stash;
	return (stash);
}

ssize_t extract_buffer(t_list **lst, t_list **lst_last, int fd)
{
    t_list  *node;
    ssize_t read_len;

	if (!lst || !(*lst))
		return (-1);
    node = malloc(sizeof(t_list));
    if (!node)
        return (-1);
    node->next = NULL;
    node->data = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!(node->data))
    {
        free(node);
        return (-1);
    }
    read_len = read(fd, node->data, BUFFER_SIZE);
    if (read_len > 0)
	{
    	node->data[read_len] = '\0';
	}
	if ((!lst) || !(*lst))
		*lst = node;
    if (lst_last && *lst_last)
        (*lst_last)->next = node;
    (*lst_last) = node;
    return (read_len);
}

char    *allocate_line_and_init(t_list *lst, size_t *i, t_list **n)
{
    size_t  len;
    t_list  *node;
    char    *line;

    len = 0;
	node = lst;
    while (node)
    {
        len += ft_strlen_to_newline(node->data);
        node = node->next;
    }
    line = malloc(sizeof(char) * (len + 1));
    if (!line)
        return (NULL);
    line[len] = '\0';
	*i = 0;
	*n = lst;
    return (line);
}

char    *parse_line_and_stash(t_list *lst, char *stash)
{
    t_list  *node;
    char    *line;
    size_t  i;
    size_t  j;
    
	line = allocate_line_and_init(lst, &i, &node);
    if (!line)
        return (NULL);
    while (node)
    {
        j = 0;
        while ((node->data)[j] && (node->data)[j] != '\n')
            line[i++] = (node->data)[j++];
		if ((node->data)[j] == '\n')
		{
			line[i] = '\n';
			i = 0;
			while ((node->data)[j] != '\0')
				stash[i++] = (node->data)[j++];
			stash[i] = '\0';
		}
		node = node->next;
    }
	return (line);
}

char	*get_next_line(int fd)
{
	t_list		*lst;
	t_list		*lst_last;
	char		*line;
	static char	stash[BUFFER_SIZE + 1];
	ssize_t		read_len;

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	lst = NULL;
	lst_last = NULL;
	if (!push_stash(stash, &lst, &lst_last))
		return (NULL);
	read_len = 1;
	while (read_len > 0 && !contains_newline(lst_last))
		read_len = extract_buffer(&lst, &lst_last, fd);
	if (read_len == -1)
		return (free_everything(lst));
	line = parse_line_and_stash(lst, stash);
	free_everything(lst);
	return (line);
}

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

int main(void)
{
    int fd = open("tests/caca.txt", O_RDONLY);
	char	*line;

	line = get_next_line(fd);
	printf("%s", line);
	line = get_next_line(fd);
	printf("%s", line);
}
