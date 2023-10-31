/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_1main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:29:08 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/31 18:03:03 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*here_doc(char *argv)
{
	char	*buffer;
	char	*ans;
	int		i;
	int		fd;

	i = 0;
	fd = dup(STDERR_FILENO);
	buffer = NULL;
	buffer = (char *)malloc(sizeof(char) * (ft_strlen(argv) + 2));
	ans = NULL;
	while (1)
	{
		if (i == 0 || buffer[i - 1] == '\n')
			write(fd, "heredoc> ", 9);
		i = read(2, buffer, ft_strlen(argv) + 1);
		buffer[i] = '\0';
		if ((i <= 0 || !ft_strncmp(buffer, argv, ft_strlen(argv)))
			&& buffer[i - 1] == '\n')
			break ;
		else
			ans = ft_strcat(ans, ft_strdup(buffer));
	}
	return (free(buffer), close(fd), ans);
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

int	check_otherbuilt(char *argv)
{
	return (ft_strcmp(argv, "echo")
		&& ft_strcmp(argv, "env") && ft_strcmp(argv, "pwd")
		&& ft_strcmp(argv, "exit"));
}

char	*get_path(char *argv, char **first_dir)
{
	char	**path;
	char	*temp;
	int		i;
	char	*stjoin;

	i = 0;
	if ((!ft_strcmp(argv, "cd") || !ft_strcmp(argv, "unset") \
		|| !ft_strcmp(argv, "export") || (!access(argv, X_OK) \
		&& check_otherbuilt(argv))) && ft_strcmp(argv, "minishell") \
		&& ft_strcmp(argv, "minishell"))
		return (argv);
	temp = ft_getenv(first_dir, ft_strndup("PATH", 4));
	path = ft_split_c(temp, ':');
	while (path[i++])
	{
		stjoin = ft_strcat(ft_strcat(ft_strdup(path[i - 1]), \
				ft_strdup("/")), ft_strdup(argv));
		if (!access(stjoin, X_OK))
			free_chardstar(path);
		if (!access(stjoin, X_OK))
			return (free(argv), stjoin);
		free(stjoin);
	}
	return (free_chardstar(path), get_path_util(argv), argv);
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
