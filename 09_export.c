/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 02:08:34 by vchulkai          #+#    #+#             */
/*   Updated: 2023/10/22 22:28:07 by ntairatt         ###   ########.fr       */
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

int	ft_export(char **envp, char *argv)
{
	size_t	i;

	i = 0;
	if (!argv)
		return (0);
	while (envp[i])
	{
		if (*argv != 0 && (ft_cmpstrn(argv, envp[i], ft_arglen(argv)) == 0))
		{
			free(envp[i]);
			envp[i] = ft_strdup(argv);
			break ;
		}
		i++;
	}
	if (!envp[i])
	{
		envp[i++] = ft_strdup(argv);
		envp[i] = NULL;
	}
	return ((int)i);
}
