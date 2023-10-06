/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_1main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:29:08 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/06 18:37:26 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *argv)
{
	char	*buffer;
	int		f;
	ssize_t	bytes_read;

	f = openfile(".here_doc", 'O');
	buffer = (char *)malloc(sizeof(char) * (ft_strlen(argv) + 1));
	if (!buffer)
		return ;
	while (write(1, "heredoc> ", 9))
	{
		while (1)
		{
			bytes_read = read(STDIN_FILENO, buffer, ft_strlen(argv) + 1);
			if (buffer[bytes_read - 1] == '\n'
				&& !ft_strncmp(buffer, argv, ft_strlen(argv)))
			{
				close(f);
				free(buffer);
				return ;
			}
			else if (write(f, buffer, bytes_read)
				&& buffer[bytes_read - 1] == '\n' && buffer)
				break ;
		}
	}
}

int	openfile(char *fname, char mode)
{
	int	fd;

	if (mode == 'I' && access(fname, R_OK))
	{
		perror(fname);
		exit(1);
	}
	else if (mode == 'I' )
		return (open(fname, O_RDONLY, O_NONBLOCK | O_SYNC | O_EXCL));
	else
	{
		fd = open(fname, O_CREAT | O_WRONLY | O_TRUNC,
				0000400 | 0000200 | 0000040 | 0000020 | 0000004 | O_NONBLOCK);
		if (fd < 0)
		{
			perror(fname);
			return (-1);
		}
	}
	return (fd);
}

char	*get_path(char *argv, char **first_dir)
{
	char	**path;
	char	*temp;
	int		i;
	char	*stjoin;

	i = 0;
	if (!ft_strcmp(argv, "cd"))
		return (argv);
	temp = ft_getenv(first_dir, ft_strndup("PATH", 4));
	path = ft_split_c(temp, ':');
	free(temp);
	while (path[i++])
	{
		stjoin = ft_strcat(ft_strcat(ft_strndup(path[i - 1],
						ft_strlen(path[i - 1])), ft_strndup("/", 1)),
				ft_strndup(argv, ft_strlen(argv)));
		if (!access(stjoin, X_OK))
			free_chardstar(path);
		if (!access(stjoin, X_OK))
			return (free(argv), stjoin);
		free(stjoin);
	}
	free_chardstar(path);
	get_path_util(argv);
	return (argv);
}

void	free_re_arg(t_argtable **temp)
{
	int			i;

	i = 0;
	free_chardstar((*temp)->redirection);
	free_chardstar((*temp)->argv);
}

char	*get_command(char *str)
{
	int		i;
	int		n;
	char	*ans;

	ans = NULL;
	n = ft_strlen(str) - 1;
	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] == '/')
			break ;
		i--;
	}
	if (i >= 0)
		ans = ft_strndup(str + i, n - i);
	else
		ans = ft_strdup(str);
	free(str);
	return (ans);
}
