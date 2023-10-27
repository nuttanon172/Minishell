/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchulkai <vchulkai@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 02:03:20 by vchulkai          #+#    #+#             */
/*   Updated: 2023/10/25 21:38:12 by vchulkai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_arglen(char *argv)
{
	size_t	i;

	i = 0;
	while (argv[i] && argv[i] != '=' && !(argv[i] == '+' && argv[i + 1] == '='))
		i++;
	return (i);
}

static void	ft_unset_util(char **envp, char *argv)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = 0;
	if (!check_ex_unset(argv, "unset"))
		return ;
	while (envp[i] && envp[j])
	{
		if (!ft_strncmp(envp[i], argv, ft_strlen(argv)))
			j++;
		temp = envp[i];
		if (!envp[j])
			break ;
		envp[i] = ft_strdup(envp[j]);
		free(temp);
		temp = NULL;
		j++;
		i++;
	}
	if (i == j)
		return ;
	free(envp[i]);
	envp[i] = 0;
}

void	ft_unset(char **envp, char **argv)
{
	int		i;

	i = 1;
	while (argv[i])
		ft_unset_util(envp, argv[i++]);
}
