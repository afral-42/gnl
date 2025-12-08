/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounoua <abounoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 14:13:10 by abounoua          #+#    #+#             */
/*   Updated: 2025/12/08 16:33:54 by abounoua         ###   ########lyon.fr   */
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

void	*free_everything(t_list *lst, char *stash, ssize_t read_len)
{
	t_list	*node;
	t_list	*temp;
	size_t	i;

	node = lst;
	while (node)
	{
		temp = node->next;
		free(node->data);
		free(node);
		node = temp;
	}
	i = 0;
	while (read_len <= 0 && i < BUFFER_SIZE)
		stash[i++] = 0;
	return (NULL);
}

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*dup;

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
	return (dup);
}
