/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 13:07:21 by ntairatt          #+#    #+#             */
/*   Updated: 2023/11/06 18:10:16 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_flagn(const char *s)
{
	size_t	i;

	i = 0;
	if (s[i] == '-')
		i++;
	while (s[i])
	{
		if (s[i] == 'n')
			i++;
		else
			return (1);
	}
	return (0);
}

int	ft_echo(char ***argv)
{
	int	i;

	i = 1;
	if (!(*argv)[i])
	{
		printf("\n");
		return (0);
	}
	if (!is_flagn((*argv)[i]))
		i++;
	while ((*argv)[i])
	{
		printf("%s", (*argv)[i]);
		i++;
		if ((*argv)[i])
			printf(" ");
	}
	if (is_flagn((*argv)[1]))
		printf("\n");
	return (0);
}

int	ft_exit(char **av)
{
	int	exit_code;

	if (!av[1])
		exit_code = 0;
	else
		exit_code = ft_atoi(av[1]);
	return (exit(exit_code), exit_code);
}

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (perror("pwd_error :"), errno);
	printf("%s\n", pwd);
	return (free(pwd), 0);
}
