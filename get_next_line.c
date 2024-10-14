/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:39:58 by jlorette          #+#    #+#             */
/*   Updated: 2024/10/14 15:45:36 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	add_storage(t_list **storage, const char *buffer, int read_return)
{
	t_list	*new_node;
	t_list	*last_node;
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
	last_node = search_last_node(*storage);
	last_node ->next = new_node;
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

static void	reset_storage(t_list **storage)
{
	t_list	*last_node;
	t_list	*reset_node;
	int		i;

	if (*storage == NULL)
		return ;
	last_node = search_last_node(*storage);
	i = 0;
	while (last_node->content[i] && last_node->content[i] != '\n')
		i++;
	if (last_node->content[i] == '\n')
		i++;
	reset_node = malloc(sizeof(t_list));
	if (!reset_node)
		return ;
	reset_node->content = copy_content_after_newline(last_node->content, i);
	if (!reset_node->content)
	{
		free(reset_node);
		return ;
	}
	reset_node->next = NULL;
	free_storage(*storage);
	*storage = reset_node;
}

char	*get_next_line(int fd)
{
	static t_list	*storage;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
	{
		storage = NULL;
		return (NULL);
	}
	line = NULL;
	read_and_stock(fd, &storage);
	if (!storage)
		return (NULL);
	create_line(storage, &line);
	reset_storage(&storage);
	if (line[0] == '\0')
	{
		free_storage(storage);
		storage = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}
