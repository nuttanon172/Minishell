/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 02:08:34 by vchulkai          #+#    #+#             */
/*   Updated: 2023/10/31 17:54:32 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**rep_envp(char **envp2, char **envp, int i, char *argv)
{
	envp2 = (char **)malloc(sizeof(char *) * (i + 2));
	if (!envp2)
		return (NULL);
	i = 0;
	while (envp[i++])
		envp2[i - 1] = ft_strdup(envp[i - 1]);
	if (argv[ft_arglen(argv)] == '+')
		envp2[i - 1] = ft_strcat(ft_strndup(argv, ft_arglen(argv)) \
			, ft_strdup((argv + ft_arglen(argv) + 1)));
	else
		envp2[i - 1] = ft_strdup(argv);
	envp2[i] = NULL;
	return (envp2);
}

static char	**ft_rpenv(char **envp, char *argv)
{
	size_t	i;
	char	**envp2;

	i = 0;
	envp2 = NULL;
	if (!argv)
		return (0);
	while (envp[i] && envp)
	{
		if (*argv != 0 && (ft_cmpstrn(argv, envp[i], ft_arglen(argv)) == 0))
		{
			if (argv[ft_arglen(argv)] == '+')
				envp[i] = ft_strcat(envp[i], \
				ft_strdup(argv + ft_arglen(argv) + 2));
			else
			{
				free(envp[i]);
				envp[i] = ft_strdup(argv);
			}
			return (envp);
		}
		i++;
	}
	envp2 = rep_envp(envp2, envp, i, argv);
	return (free_chardstar(envp), envp2);
}

char	**ft_export(char **envp, char **argv)
{
	int		i;
	char	**temp;

	i = 0;
	temp = argv;
	temp++;
	if (!*temp)
	{
		while (envp[i])
			printf("declare -x %s\n", envp[i++]);
	}
	else
	{
		while (*temp)
		{
			if (check_ex_unset(*temp, "export"))
				envp = ft_rpenv(envp, *temp);
			temp++;
		}
	}
	return (envp);
}
