/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:29:57 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/08 13:02:22 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>

size_t	ft_strlen(const char *s)
{
	size_t	ct;

	if (!s)
		return (0);
	ct = 0;
	while (s[ct] != '\0')
		ct++;
	return (ct);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
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

size_t	ft_arglen(char *argv)
{
	size_t	i;

	i = 0;
	while (argv[i] && argv[i] != '=')
		i++;
	return (i);
}

void	ft_unset(char **envp, char *argv)
{
	int		i[2];
	size_t	len[2];

	i[0] = 0;
	if ((ft_strlen(argv) != ft_arglen(argv)))
		write(2, "minishell: unset: not a valid identifier\n", 42);
	if (!argv || (ft_strlen(argv) != ft_arglen(argv)))
		return ;
	i[1] = open(".minishell.env", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	len[0] = ft_strlen(argv);
	while (envp[i[0]])
	{
		len[1] = ft_arglen(envp[i[0]]);
		if (len[1] < len[0])
			len[1] = len[0];
		if (ft_strncmp(argv, envp[i[0]], len[1]) != 0)
		{
			write(i[1], envp[i[0]], ft_strlen(envp[i[0]]));
			write (i[1], "\n", 1);
		}
		(i[0])++;
	}
	close(i[1]);
}

int	main(int argc, char **argv, char **env)
{
	if (argc == 1)
		return (0);
	ft_unset(env, argv[1]);
	return (0);
}
