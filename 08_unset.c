/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 02:03:20 by vchulkai          #+#    #+#             */
/*   Updated: 2023/10/22 22:28:29 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	**temp;
	char	**temp2;

	temp = envp;
	temp2 = envp;
	if ((ft_strlen(argv) != ft_arglen(argv)))
		write(2, "minishell: unset: not a valid identifier\n", 42);
	if (!argv || (ft_strlen(argv) != ft_arglen(argv)))
		return ;
	while (*temp)
	{
		if (!ft_strncmp(*temp, argv, ft_strlen(argv)))
			temp2++;
		if (*temp && !*temp2)
		{
			free(*temp);
			*temp = NULL;
			break ;
		}
		if (*temp2 && *temp != *temp2)
			*temp = *temp2;
		temp++;
		temp2++;
	}
}
