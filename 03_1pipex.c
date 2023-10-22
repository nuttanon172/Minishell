/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_1pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:53:47 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/22 22:27:11 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_file_des(int fds, char *s, char c)
{
	int	fd;
	int	writefile;
	int	pid;
	int	status;

	fd = dup(fds);
	writefile = 0;
	if (c == 'o')
		writefile = open(s, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (c == 'a')
		writefile = open(s, O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (c == 0)
		writefile = STDOUT_FILENO;
	pid = fork();
	if (!pid)
	{
		write_to_file_pfd(fd, writefile);
		close(fd);
	}
	waitpid(pid, &status, 0);
	close(writefile);
	close(fd);
}

void	write_to_file_pfd(int fd, int writefile)
{
	size_t	i;
	char	*ans;
	char	str[11];

	i = 0;
	ans = NULL;
	while (1)
	{
		i = read(fd, str, 10);
		str[10] = 0;
		ans = ft_strcat(ans, ft_strndup(str, i));
		if (i < 10 || (i == 10 && !str[i - 1]))
			break ;
	}
	write(writefile, ans, ft_strlen(ans));
	free(ans);
	close(writefile);
	close(fd);
	exit(0);
}

char	*open_inputdoc(char *filename)
{
	struct stat	st;
	char		*string;
	int			fd;

	fd = open(filename, O_RDONLY, 0777);
	if (fd < 0)
		perror(filename);
	stat(filename, &st);
	string = (char *)malloc(sizeof(char) * (st.st_size + 1));
	if (!string)
		return (NULL);
	read(fd, string, st.st_size);
	string[st.st_size] = '\0';
	close(fd);
	return (string);
}

void	write_input_dummy(char *string)
{
	int	fd;

	fd = open(".input_file", O_CREAT | O_RDWR, 0777);
	write(fd, string, ft_strlen(string));
	free(string);
	close(fd);
}
