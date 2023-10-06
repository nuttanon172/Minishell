/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 19:35:32 by naam              #+#    #+#             */
/*   Updated: 2023/10/06 19:54:26 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unset.h"

void	ft_unset(char **envp, char *argv)
{
	int		i[2];
	size_t	len[2];

	i[0] = 0;
	if ((ft_strlen(argv) != ft_arglen(argv)))
		write (2, "minishell: unset: not a valid identifier\n", 42);
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
