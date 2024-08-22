/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlorette <jlorette@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 13:26:24 by jlorette          #+#    #+#             */
/*   Updated: 2024/08/22 13:26:34 by jlorette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main()
{
	int	fd = open("test.txt", O_RDONLY);
	char *s;
	s = get_next_line(fd);
	printf("%s\n", s);
    free(s);
	while (s)
    {
        s = get_next_line(fd);
        printf("%s\n", s);
        free(s);
    }
    close(fd);
	return 0;
}
