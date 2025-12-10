/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abounoua <abounoua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 19:08:52 by abounoua          #+#    #+#             */
/*   Updated: 2025/12/10 15:23:19 by abounoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# define FD_MAX 1024

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
void	*free_everything_b(t_list *lst,
			char stash[FD_MAX][BUFFER_SIZE + 1], ssize_t read_len, int fd);
char	*ft_strdup(const char *s);

#endif
