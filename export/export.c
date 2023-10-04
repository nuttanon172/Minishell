/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbhuprad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:35:23 by naam              #+#    #+#             */
/*   Updated: 2023/09/26 15:01:43 by lbhuprad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "export.h"

int	ft_replace(char **envp, char *argv)
{
	int	i[2];

	i[0] = 0;
	if (!argv)
		return (0);
	while (envp[i[0]])
	{
		if (*argv != 0 && (ft_strncmp(argv, envp[i[0]], ft_arglen(argv)) == 0))
		{
			free(envp[i[0]]);
			envp[i[0]] = NULL;
			envp[i[0]] = ft_strdup(argv);
			break ;
		}
		(i[0])++;
	}
	return (i[0]);
}

void	ft_export(char **envp, char *argv)
{
	int		i[2];

	i[0] = ft_replace(envp, argv);
	if (!envp[i[0]] && ((i[0]) > 0))
	{
		i[1] = open(".minishell.env", O_WRONLY | O_APPEND, 0644);
		write(i[1], argv, ft_strlen(argv));
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

int	main(int argc, char **argv)
{
	if (argc == 1)
		return (0);
	ft_export(ft_splitenv(), argv[1]);
	return (0);
}
