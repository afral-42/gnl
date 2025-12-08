/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounoua <abounoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:08:52 by abounoua          #+#    #+#             */
/*   Updated: 2025/12/08 10:06:54 by abounoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
#endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
    char			*data;
    struct s_list	*next;
}	t_list;

size_t	ft_strlen_to_newline(char *str);
size_t	contains_newline(t_list *lst_last);
char	*get_next_line(int fd);
void	*free_everything(t_list *lst, char *stash, ssize_t read_len);

#endif
