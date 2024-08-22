/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:50:53 by jlorette          #+#    #+#             */
/*   Updated: 2024/08/22 23:59:30 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

void	add_storage(t_list **storage, char *buffer, int read_return);
void	alloc_line(char **line, t_list *storage);
char	*copy_content_after_newline(char *content, int start);
void	create_line(t_list *storage, char **line);
void	free_storage(t_list *storage);
char	*get_next_line(int fd);
void	read_and_stock(int fd, t_list **storage);
void	reset_storage(t_list **storage);
int		search_new_line(t_list *storage);
t_list	*search_last_node(t_list *storage);

#endif
