/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:26:24 by jlorette          #+#    #+#             */
/*   Updated: 2024/08/23 12:29:39 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main()
{
	int	i = 0;
	int	fd = open("test.txt", O_RDONLY);
	char *s;
	s = get_next_line(fd);
	printf("line: %d: %s",i, s);
	i++;
    free(s);
	while (s)
    {
        s = get_next_line(fd);
		printf("line: %d: %s",i, s);
        free(s);
		i++;
    }
    close(fd);
	return 0;
}