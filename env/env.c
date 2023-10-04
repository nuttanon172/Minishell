/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbhuprad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:30:10 by naam              #+#    #+#             */
/*   Updated: 2023/09/26 14:46:39 by lbhuprad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	struct stat	st;
	char		*string;
	int			fd;

	fd = open(".minishell.env", O_RDONLY);
	stat(".minishell.env", &st);
	string = malloc(sizeof(char) * (st.st_size) + 1);
	string[st.st_size] = '\0';
	read(fd, string, st.st_size);
	printf("%s", string);
	close(fd);
	free(string);
	return (0);
}
