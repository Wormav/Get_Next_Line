/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 13:15:34 by jlorette          #+#    #+#             */
/*   Updated: 2024/08/23 18:15:10 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

t_list	*search_last_node(t_list *storage)
{
	t_list	*current;

	current = storage;
	while (current && current->next)
		current = current->next;
	return (current);
}

void	free_storage(t_list *storage)
{
	t_list	*current;
	t_list	*next;

	current = storage;
	while (current)
	{
		free(current->content);
		next = current->next;
		free(current);
		current = next;
	}
}

void	alloc_line(char **line, t_list *storage)
{
	int	i;
	int	len;

	len = 0;
	while (storage)
	{
		i = 0;
		while (storage->content[i])
		{
			len++;
			if (storage->content[i] == '\n')
				break ;
			i++;
		}
		storage = storage->next;
	}
	*line = malloc(sizeof(char) * (len + 1));
}

char	*copy_content_after_newline(char *content, int start)
{
	char	*new_content;
	int		length;
	int		i;

	length = 0;
	while (content[start + length])
		length++;
	new_content = malloc(sizeof(char) * (length + 1));
	if (!new_content)
		return (NULL);
	i = 0;
	while (content[start])
		new_content[i++] = content[start++];
	new_content[i] = '\0';
	return (new_content);
}
