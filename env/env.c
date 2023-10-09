/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:14:52 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/09 16:33:25 by ntairatt         ###   ########.fr       */
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
	string = (char *)malloc(sizeof(char) * (st.st_size + 1));
	if (!string)
		return (close(fd), EXIT_FAILURE);
	string[st.st_size] = '\0';
	read(fd, string, st.st_size);
	printf("%s", string);
	return (close(fd), free(string), 0);
}
