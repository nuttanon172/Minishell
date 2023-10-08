/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_0utils_env_split_ok.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:42:46 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/08 16:48:02 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_env_utils(int fd, char **envp, char *first_dir)
{
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5))
			write(fd, *envp, ft_strlen(*envp));
		else
		{
			write(fd, *envp, 5);
			write(fd, first_dir, ft_strlen(first_dir));
			write(fd, "/bin/:", 6);
			write(fd, *envp + 5, ft_strlen(*envp + 5));
		}
		write(fd, "\n", 1);
		envp++;
	}
}

void	write_env(char **envp, char *first_dir)
{
	int			fd;
	struct stat	st;
	char		*file_path;

	file_path = ft_strcat(ft_strdup(first_dir), ft_strdup("/.minishell.env"));
	fd = open(file_path, O_WRONLY | O_CREAT, 0777);
	stat(file_path, &st);
	if (!st.st_size)
		write_env_utils(fd, envp, first_dir);
	close(fd);
	free(file_path);
}

char	**ft_splitenv(char *first_dir)
{
	int			fd[2];
	char		**envp;
	char		*ans;
	char		*file_dirs;
	char		str[11];

	ans = NULL;
	envp = NULL;
	file_dirs = ft_strcat(ft_strdup(first_dir), ft_strdup("/.minishell.env"));
	fd[0] = open(file_dirs, O_RDONLY, 0777);
	while (1)
	{
		fd[1] = read(fd[0], str, 10);
		str[10] = 0;
		if (fd[1] <= 0)
			break ;
		ans = ft_strcat(ans, ft_strndup(str, fd[1]));
	}
	envp = ft_split_to_env(ans, '\n');
	return (free(ans), free(file_dirs), close(fd[0]), envp);
}

char	**ft_split_to_env(char *string, char ch)
{
	size_t	j;
	size_t	k;
	char	**ans;
	char	*temp;

	j = 0;
	temp = string;
	k = count_newline(temp);
	ans = (char **)malloc(sizeof(char *) * (k + 1));
	while (*temp)
	{
		ans[j++] = ft_strndup(temp, count_to_newline(temp));
		while (*temp)
		{
			if (*temp == ch)
			{
				temp++;
				break ;
			}
			temp++;
		}
	}
	temp = NULL;
	ans[k] = NULL;
	return (ans);
}

int	count_to_newline(char *src)
{
	char	*temp;
	int		i;

	i = 0;
	temp = src;
	while (*temp)
	{
		if (*temp == '\n' || !*temp)
		{
			if (!*temp)
				i--;
			break ;
		}
		i++;
		temp++;
	}
	return (i);
}
