/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:44:51 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/07 22:17:35 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

static int	ft_cmpstrn(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n) && ((s1[i] != '\0') || (s2[i] != '\0')))
	{
		if (s1[i] > s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] < s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	update_env(char **temp)
{
	int		fd;
	size_t	i;
	size_t	j;

	i = 0;
	fd = open(".minishell.env", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (temp[i])
	{
		j = 0;
		while (temp[i][j])
			write(fd, &temp[i][j++], 1);
		free(temp[i]);
		temp[i] = NULL;
		i++;
	}
	free(temp);
}

int	ft_replace(char *argv, char **temp)
{
	int	i;

	i = 0;
	if (!argv)
		return (0);
	while (temp[i])
	{
		if (*argv != 0 && (ft_cmpstrn(argv, temp[i], ft_arglen(argv)) == 0))
		{
			free(temp[i]);
			temp[i] = NULL;
			temp[i] = ft_strdup(argv);
			update_env(temp);
			break ;
		}
		i++;
	}
	return (i);
}

void	ft_export(char *argv, char **temp, char **envp)
{
	int		i[2];

	i[0] = ft_replace(argv, temp);
	if (!envp[i[0]] && ((i[0]) > 0))
	{
		i[1] = open(".minishell.env", O_WRONLY | O_APPEND, 0644);
		write(i[1], argv, ft_strlen(argv));
		write(i[1], "\n", 1);
		close(i[1]);
		return ;
	}
	i[0] = 0;
	i[1] = open(".minishell.env", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (envp[i[0]])
	{
		write(i[1], envp[i[0]], ft_strlen(envp[i[0]]));
		write (i[1], "\n", 1);
		(i[0])++;
		printf("envp: %s\n", envp[i[0]]);
	}
	close(i[1]);
}

int	main(int argc, char **argv, char **env)
{
	size_t	i;
	char	**temp;

	i = 0;
	temp = NULL;
	while (env[i])
	{	
		temp[i] = ft_strdup(env[i]);
		i++;
	}
	temp[i] = 0;
	if (argc == 1)
		return (0);
	ft_export(argv[1], temp, env);
	return (0);
}
