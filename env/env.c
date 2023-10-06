/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:14:52 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/06 19:40:37 by ntairatt         ###   ########.fr       */
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
	string = (char *)malloc(sizeof(char) * (st.st_size) + 1);
	string[st.st_size] = '\0';
	read(fd, string, st.st_size);
	printf("%s", string);
	close(fd);
	free(string);
	return (0);
}
