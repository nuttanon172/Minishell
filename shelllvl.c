/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shelllvl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:36:23 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/31 17:36:37 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_strddup(char **envp)
{
	int		i;
	char	**temp;
	char	**env;

	i = 0;
	temp = envp;
	while (*temp && temp)
	{
		i++;
		temp++;
	}
	env = (char **)malloc(sizeof(char *) * (i + 1));
	env[i--] = NULL;
	temp = envp;
	while (i >= 0)
	{
		env[i] = ft_strdup(temp[i]);
		i--;
	}
	return (env);
}

int	check_in_env(char **envp, char *check)
{
	char	**temp;

	temp = envp;
	while (*temp)
	{
		if (!ft_strncmp(*temp, "SHELL=", 6))
		{
			if (!ft_strcmp(*temp, check))
				return (1);
			if (ft_strlen(*temp) > 9
				&& !ft_strcmp(*temp + ft_strlen(*temp) - 9, "minishell"))
				return (1);
		}
		temp++;
	}
	return (0);
}

void	my_env(char **envp, char *first_dir)
{
	char	**temp_env;
	int		i;
	char	*value;

	temp_env = envp;
	value = ft_strcat(ft_strcat(ft_strdup("SHELL="),
				ft_strdup(first_dir)), ft_strdup("/minishell"));
	i = check_in_env(envp, value);
	while (*temp_env)
	{
		if (!i && !ft_strncmp(*temp_env, "PATH=", 5))
			add_path(temp_env, first_dir);
		else if (!i && !ft_strncmp(*temp_env, "SHELL=", 6))
		{
			free(*temp_env);
			*temp_env = ft_strdup(value);
		}
		if (!ft_strncmp(*temp_env, "SHLVL=", 6))
			change_level(temp_env);
		temp_env++;
	}
	free(value);
}

void	change_level(char **temp_env)
{
	char	*temp;

	temp = *temp_env;
	*temp_env = ft_strcat(ft_strdup("SHLVL="),
			ft_itoa(ft_atoi(*temp_env) + 1));
	free(temp);
}

void	add_path(char **env, char *first_dir)
{
	char	*path1;
	char	*path2;
	char	*remain;
	char	*temp;

	temp = *env;
	path1 = ft_strcat(ft_strdup("PATH="), ft_strdup(first_dir));
	path1 = ft_strcat(path1, ft_strdup("/bin:"));
	path2 = ft_strcat(ft_strdup(first_dir), ft_strdup(":"));
	remain = ft_strdup(temp + 5);
	free(*env);
	*env = ft_strcat(ft_strcat(path1, path2), remain);
}
