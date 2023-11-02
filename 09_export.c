/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchulkai <vchulkai@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 02:08:34 by vchulkai          #+#    #+#             */
/*   Updated: 2023/11/02 18:11:35 by vchulkai         ###   ########.fr       */
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

char	**rep_envp(char **envp, int i, char *argv)
{
	char	**envp2;

	envp2 = (char **)malloc(sizeof(char *) * (i + 2));
	if (!envp2)
		return (NULL);
	envp[i] = NULL;
	i = -1;
	while (envp[++i])
		envp2[i] = envp[i];
	if (argv[ft_arglen(argv)] == '+')
		envp2[i++] = ft_strcat(ft_strndup(argv, ft_arglen(argv)) \
			, ft_strdup((argv + ft_arglen(argv) + 1)));
	else
		envp2[i++] = ft_strdup(argv);
	envp2[i] = NULL;
	return (envp2);
}

void	ft_rpenv(char ***envp, char *argv)
{
	int	i;

	i = 0;
	if (!argv)
		return ;
	while ((*envp)[i])
	{
		if (*argv != 0 && (ft_cmpstrn(argv, (*envp)[i], ft_arglen(argv)) == 0))
		{
			if (argv[ft_arglen(argv)] == '+')
			{
				(*envp)[i] = ft_strcat((*envp)[i], \
				ft_strdup(argv + ft_arglen(argv) + 2));
			}
			else
			{
				free((*envp)[i]);
				(*envp)[i] = ft_strdup(argv);
			}
			return ;
		}
		i++;
	}
	*envp = rep_envp(*envp, i, argv);
}

void	ft_export(char ***envp, char **argv)
{
	int		i;
	char	**temp;

	i = 0;
	temp = argv;
	temp++;
	if (!*temp)
	{
		while ((*envp)[i])
			printf("declare -x %s\n", (*envp)[i++]);
	}
	else
	{
		while (*temp)
		{
			if (check_ex_unset(*temp, "export"))
				ft_rpenv(envp, *temp);
			temp++;
		}
	}
}
