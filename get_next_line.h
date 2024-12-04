/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:31:39 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/04 14:53:06 by jlorette         ###   ########.fr       */
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

void	alloc_line(char **line, t_list *storage);
char	*copy_after_newline(const char *content, int start);
void	free_storage(t_list *storage);
char	*get_next_line(int fd);
int		search_new_line(t_list *storage);
t_list	*last_node(t_list *storage);

#endif
