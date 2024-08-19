/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:50:56 by jlorette          #+#    #+#             */
/*   Updated: 2024/08/19 15:06:54 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

int		search_new_line(t_list *storage);
void	read_and_stock(int fd, t_list **storage);
void	add_storage(t_list **storage, char *buffer, int read_return);
t_list	*search_last_node(t_list *storage);
void	alloc_line(char **line, t_list *storage);
void	free_storage(t_list *storage);
int		ft_strlen(const char *str);

#endif
