/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:44:51 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/08 14:33:46 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

size_t	ft_arglen(char *argv)
{
	size_t	i;

	i = 0;
	while (argv[i] && argv[i] != '=')
		i++;
	return (i);
}

int	ft_cmpstrn(const char *s1, const char *s2, size_t n)
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

int	ft_replace(char **envp, char *argv)
{
	size_t	i;

	i = 0;
	if (!argv)
		return (0);
	while (envp[i])
	{
		if (*argv != 0 && (ft_cmpstrn(argv, envp[i], ft_arglen(argv)) == 0))
		{
			envp[i] = ft_strdup(argv);
			break ;
		}
		i++;
	}
	if (!envp[i])
		envp[i] = ft_strdup(argv);
	i++;
	return ((int)i);
}

void	ft_export(char **envp, char *argv)
{
	size_t	i;
	int		fd;

	i = ft_replace(envp, argv);
	i = 0;
	fd = open(".minishell.env", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (envp[i])
	{
		write(fd, envp[i], ft_strlen(envp[i]));
		printf("envp[i] = %s\n", envp[i]);
		write (fd, "\n", 1);
		i++;
	}
	close(fd);
}

int	main(int argc, char **argv, char **env)
{
	if (argc == 1)
		return (0);
	ft_export(env, argv[1]);
	return (0);
}
