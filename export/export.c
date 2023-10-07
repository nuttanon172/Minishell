/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:44:51 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/07 22:37:28 by ntairatt         ###   ########.fr       */
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

int	ft_replace(char ***envp, char *argv)
{
	int	i[2];

	i[0] = 0;
	if (!argv)
		return (0);
	while ((*envp)[i[0]])
	{
		if (*argv != 0 && (ft_cmpstrn(argv, (*envp)[i[0]], ft_arglen(argv)) == 0))
		{
			(*envp)[i[0]] = NULL;
			(*envp)[i[0]] = ft_strdup(argv);
			break ;
		}
		(i[0])++;
	}
	if (!(*envp)[i[0]])
		(*envp)[i[0]] = ft_strdup(argv);
	(i[0])++;
	return (i[0]);
}

void	ft_export(char **envp, char *argv)
{
	int		i[2];

	i[0] = ft_replace(&envp, argv);
	i[0] = 0;
	i[1] = open(".minishell.env", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (envp[i[0]])
	{
		write(i[1], envp[i[0]], ft_strlen(envp[i[0]]));
		write (i[1], "\n", 1);
		(i[0])++;
	}
	close(i[1]);
}

int	main(int argc, char **argv, char **env)
{
	if (argc == 1)
		return (0);
	ft_export(env, argv[1]);
	return (0);
}
