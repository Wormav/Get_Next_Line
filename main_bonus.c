/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:26:24 by jlorette          #+#    #+#             */
/*   Updated: 2024/08/23 15:07:12 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int	main()
{
	int		i;
	int		fd1, fd2;
	char	*s;

	// Lecture du premier fichier "test.txt"
	i = 0;
	fd1 = open("test.txt", O_RDONLY);
	if (fd1 < 0)
		return (1);
	s = get_next_line(fd1);
	while (s)
	{
		printf("File 1, line %d: %s", i, s);
		free(s);
		i++;
		s = get_next_line(fd1);
	}
	close(fd1);

	// Lecture du deuxième fichier "test2.txt"
	i = 0;
	fd2 = open("test2.txt", O_RDONLY);
	if (fd2 < 0)
		return (1);
	s = get_next_line(fd2);
	while (s)
	{
		printf("File 2, line %d: %s", i, s);
		free(s);
		i++;
		s = get_next_line(fd2);
	}
	close(fd2);

	return (0);
}