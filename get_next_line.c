/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 13:06:00 by jlorette          #+#    #+#             */
/*   Updated: 2024/08/22 14:19:16 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*storage;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
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
			if (storage->content[i] == '\n')
				break ;
			(*line)[j++] = storage->content[i++];
		}
		storage = storage->next;
	}
	(*line)[j] = '\0';
}

void reset_storage(t_list **storage)
{
	t_list *last_node;
	t_list *reset_node;
	int i;
	int length;

	// Vérifie si la liste est vide
	if (*storage == NULL)
		return;

	// Trouve le dernier nœud de la liste
	last_node = search_last_node(*storage);

	// Trouve l'index du caractère '\n'
	i = 0;
	while (last_node->content[i] && last_node->content[i] != '\n')
		i++;

	// Si le caractère '\n' est trouvé, passe à l'index suivant
	if (last_node->content[i] == '\n')
		i++;

	// Calcule la longueur du nouveau contenu après '\n'
	length = ft_strlen(last_node->content) - i;

	// Alloue de la mémoire pour le nouveau nœud
	reset_node = malloc(sizeof(t_list));
	if (!reset_node)
		return;

	// Alloue de la mémoire pour le contenu du nouveau nœud
	reset_node->content = malloc(sizeof(char) * (length + 1));
	if (!reset_node->content)
	{
		free(reset_node);
		return;
	}

	// Copie le contenu après '\n' dans le nouveau nœud
	for (int j = 0; j < length; j++)
		reset_node->content[j] = last_node->content[i + j];
	reset_node->content[length] = '\0'; // Ajoute le caractère de fin de chaîne

	// Initialise le pointeur 'next' du nouveau nœud
	reset_node->next = NULL;

	// Libère la mémoire de la liste originale
	free_storage(*storage);

	// Met à jour le pointeur 'storage' avec le nouveau nœud
	*storage = reset_node;
}
