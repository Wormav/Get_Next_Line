/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 13:06:00 by jlorette          #+#    #+#             */
/*   Updated: 2024/08/23 18:13:34 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_fd_storage	storages[FD_SETSIZE];
	char				*line;
	int					i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	while (i < FD_SETSIZE && storages[i].fd && storages[i].fd != fd)
		i++;
	if (i == FD_SETSIZE)
		return (NULL);
	if (storages[i].fd == 0)
		storages[i].fd = fd;
	read_and_stock(fd, &storages[i].storage);
	create_line(storages[i].storage, &line);
	if (!storages[i].storage || !line)
		return (NULL);
	reset_storage(&storages[i].storage);
	if (line[0] != '\0')
		return (line);
	free_storage(storages[i].storage);
	storages[i].storage = NULL;
	free(line);
	return (NULL);
}

void	add_storage(t_list **storage, char *buffer, int read_return)
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

void	create_line(t_list *storage, char **line)
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

void	reset_storage(t_list **storage)
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
