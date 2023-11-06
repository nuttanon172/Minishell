/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_1main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:29:08 by ntairatt          #+#    #+#             */
/*   Updated: 2023/11/06 10:56:17 by ntairatt         ###   ########.fr       */
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
		if ((i <= 0 || (((!ans || (ft_strlen(ans) > 0 && ans[ft_strlen(ans) - \
			1] == '\n')) && !ft_strncmp(buffer, argv, ft_strlen(argv))) \
			&& buffer[i - 1] == '\n')))
			break ;
		else
			ans = ft_strcat(ans, ft_strdup(buffer));
	}
	return (free(buffer), close(fd), ans);
}

int	check_otherbuilt(char *argv)
{
	return (ft_strcmp(argv, "echo")
		&& ft_strcmp(argv, "env") && ft_strcmp(argv, "pwd")
		&& ft_strcmp(argv, "exit"));
}

void	get_path_util(char *argv)
{
	if (ft_strcmp(argv, "cd"))
	{
		write(2, argv, ft_strlen(argv));
		write(2, ": Command not found\n", 20);
	}
}

char	*get_path(char *argv, char **first_dir)
{
	char	**path;
	int		i;
	char	*stjoin;

	i = 0;
	if ((!ft_strcmp(argv, "cd") || !ft_strcmp(argv, "unset") \
		|| !ft_strcmp(argv, "export") || (!access(argv, X_OK) \
		&& check_otherbuilt(argv))) && ft_strcmp(argv, "minishell"))
		return (argv);
	path = ft_split_c(ft_getenv(first_dir, ft_strndup("PATH", 4)), ':');
	if (!path)
		return (free_null(argv), NULL);
	while (path[i++])
	{
		if (*argv != '/' && *argv != '.')
			stjoin = ft_strcat(ft_strcat(ft_strdup(path[i - 1]), \
					ft_strdup("/")), ft_strdup(argv));
		else
			stjoin = ft_strdup(argv);
		if (!access(stjoin, X_OK))
			return (free_chardstar(path), free(argv), stjoin);
		free(stjoin);
	}
	return (free_chardstar(path), get_path_util(argv), argv);
}

void	free_s(char *command, char **check)
{
	if (command)
		free(command);
	if (check)
		free_chardstar(check);
	wait(NULL);
	if (!access(".here_doc", F_OK))
		unlink(".here_doc");
	if (!access(".input_file", F_OK))
		unlink(".input_file");
}
