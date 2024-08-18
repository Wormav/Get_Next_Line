/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 13:18:07 by jlorette          #+#    #+#             */
/*   Updated: 2024/08/18 13:51:24 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	search_new_line(t_list *storage)
{
	t_list	*current;
	int		i;

	current = storage;
	while (current != NULL)
	{
		i = 0;
		while (current->content[i])
		{
			if (current->content[i] == '\n')
				return (1);
			i++;
		}
		current = current->next;
	}
	return (0);
}

void	read_and_stock(int fd, t_list **storage)
{
	char	*buffer;
	int		read_return;

	read_return = 1;
	while (!search_new_line(*storage) && read_return != 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buffer)
			return ;
		read_return = (int)read(fd, buffer, BUFFER_SIZE);
		if ((*storage == NULL && read_return == 0) || read_return == -1)
		{
			free(buffer);
			return ;
		}
		buffer[read_return] = '\0';
		add_storage(storage, buffer, read_return);
		free(buffer);
	}

}

void	add_storage(t_list **storage, char *buffer, int read_return)
{}
