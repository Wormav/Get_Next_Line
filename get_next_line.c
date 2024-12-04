/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:39:58 by jlorette          #+#    #+#             */
/*   Updated: 2024/12/04 14:54:54 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	add_storage(t_list **storage, const char *buffer, int read_return)
{
	t_list	*new_node;
	t_list	*last;
	int		i;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (read_return + 1));
	if (new_node->content == NULL)
		return ;
	i = 0;
	while (buffer[i] && i < read_return)
	{
		new_node->content[i] = buffer[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*storage == NULL)
	{
		*storage = new_node;
		return ;
	}
	last = last_node(*storage);
	last ->next = new_node;
}

static void	read_and_stock(int fd, t_list **storage)
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
		if (read_return == -1)
		{
			free_storage(*storage);
			*storage = NULL;
		}
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

static void	create_line(t_list *storage, char **line)
{
	int	i;
	int	j;

	*line = NULL;
	if (!storage)
		return ;
	alloc_line(line, storage);
	if (!*line)
		return ;
	j = 0;
	while (storage)
	{
		i = 0;
		while (storage->content[i])
		{
			(*line)[j++] = storage->content[i];
			if (storage->content[i] == '\n')
				break ;
			i++;
		}
		if (storage->content[i] == '\n')
			break ;
		storage = storage->next;
	}
	(*line)[j] = '\0';
}

static void	reset_storage(t_list **storage, int fd)
{
	t_list	*reset_node;
	int		i;

	if (*storage == NULL)
		return ;
	i = 0;
	while (last_node(*storage)->content[i]
		&& last_node(*storage)->content[i] != '\n')
		i++;
	if (last_node(*storage)->content[i] == '\n')
		i++;
	reset_node = malloc(sizeof(t_list));
	if (!reset_node)
		return ;
	reset_node->content = copy_after_newline(last_node(*storage)->content, i);
	if (!reset_node->content)
	{
		free(reset_node);
		return ;
	}
	reset_node->next = NULL;
	free_storage(*storage);
	if (fd == 0)
		free_storage(reset_node);
	*storage = reset_node;
}

char	*get_next_line(int fd)
{
	static t_list	*storage;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		storage = NULL;
		return (NULL);
	}
	read_and_stock(fd, &storage);
	if (!storage)
	{
		free_storage(storage);
		return (NULL);
	}
	create_line(storage, &line);
	reset_storage(&storage, fd);
	if (line[0] == '\0')
	{
		free_storage(storage);
		storage = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}
