/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounoua <abounoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:13:10 by abounoua          #+#    #+#             */
/*   Updated: 2025/12/11 23:21:11 by abounoua         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_list	*push_stash(const char *s, t_list **lst, t_list **lst_last)
{
	char	*dup;
	t_list	*stash;

	dup = ft_strdup(s);
	if (!dup)
		return (NULL);
	stash = malloc(sizeof(t_list));
	if (!stash)
	{
		free(dup);
		return (NULL);
	}
	stash->next = NULL;
	stash->data = dup;
	*lst = stash;
	*lst_last = stash;
	return (stash);
}

static ssize_t	extract_buffer(t_list **lst, t_list **lst_last, int fd)
{
	t_list	*node;
	ssize_t	read_len;

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
	if (read_len >= 0)
		node->data[read_len] = '\0';
	if ((!lst) || !(*lst))
		*lst = node;
	if (lst_last && *lst_last)
		(*lst_last)->next = node;
	(*lst_last) = node;
	return (read_len);
}

static char	*allocate_line_and_init(t_list *lst, size_t *i, t_list **n)
{
	size_t	len;
	t_list	*node;
	char	*line;

	len = 0;
	node = lst;
	while (node)
	{
		len += ft_strlen_to_newline(node->data);
		node = node->next;
	}
	if (!len)
		return (NULL);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	line[len] = '\0';
	*i = 0;
	*n = lst;
	return (line);
}

static char	*parse_line_and_stash(t_list *lst,
	char stash[FD_MAX][BUFFER_SIZE + 1], int fd)
{
	t_list	*node;
	char	*line;
	size_t	i;
	size_t	j;

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
			j++;
			i = 0;
			while ((node->data)[j] != '\0')
				stash[fd][i++] = (node->data)[j++];
			stash[fd][i] = '\0';
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
	static char	stash[FD_MAX][BUFFER_SIZE + 1];
	ssize_t		read_len;

	lst = NULL;
	lst_last = NULL;
	if (fd < 0 || BUFFER_SIZE < 0)
		return (free_everything_b(lst, stash, -1, fd));
	if (!push_stash(stash[fd], &lst, &lst_last))
		return (NULL);
	read_len = 1;
	while (read_len > 0 && !contains_newline(lst_last))
		read_len = extract_buffer(&lst, &lst_last, fd);
	if (read_len == -1)
		return (free_everything_b(lst, stash, read_len, fd));
	line = parse_line_and_stash(lst, stash, fd);
	free_everything_b(lst, stash, read_len, fd);
	return (line);
}
