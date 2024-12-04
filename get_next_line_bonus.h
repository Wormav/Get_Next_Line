/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:50:53 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/04 15:26:29 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef FD_SETSIZE
#  define FD_SETSIZE 1024
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_fd_storage
{
	int		fd;
	t_list	*storage;
}				t_fd_storage;

void	alloc_line(char **line, t_list *storage);
char	*copy_after_newline(char *content, int start);
void	free_storage(t_list *storage);
char	*get_next_line(int fd);
int		search_new_line(t_list *storage);
t_list	*last_node(t_list *storage);

#endif
