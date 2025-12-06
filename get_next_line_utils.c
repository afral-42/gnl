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
