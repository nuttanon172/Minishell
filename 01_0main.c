/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_0main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchulkai <vchulkai@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:13:30 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/20 05:22:35 by vchulkai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	first_dir[4096];
	char	**env;

	(void)argc;
	(void)argv;
	g_pi = 0;
	getcwd(first_dir, sizeof(first_dir));
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	env = ft_strddup(envp);
	my_env(env, first_dir);
	g_pi = start_shell(env);
	return (g_pi);
}

char	**ft_strddup(char **envp)
{
	int		i;
	char	**temp;
	char	**env;

	i = 0;
	temp = envp;
	while (*temp)
	{
		i++;
		temp++;
	}
	env = (char **)malloc(sizeof(char *) * (i + 1));
	env[i--] = NULL;
	temp = envp;
	while (i >= 0)
	{
		env[i] = ft_strdup(*temp);
		i--;
		temp++;
	}
	return (env);
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
		else if (i && !ft_strncmp(*temp_env, "SHLVL=", 6))
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

int	check_in_env(char **envp, char *check)
{
	char	**temp;

	temp = envp;
	while (*temp)
	{
		if (!ft_strcmp(*temp, check))
			return (1);
		temp++;
	}
	return (0);
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

int	ft_atoi(char *nbr)
{
	int		ans;
	char	*temp;

	temp = nbr;
	ans = 0;
	while (*temp && (*temp < '0' || *temp > '9'))
		temp++;
	while (*temp && *temp >= '0' && *temp <= '9')
	{
		ans = (10 * (ans) + (*temp - '0'));
		temp++;
	}
	return (ans);
}

// char	*gnl(char *line)
// {
// 	int		i;
// 	char	*ans;

// 	i=0;
// 	while (line[i] && line[i] != '\n')
// 		i++;
// 	// if (line[i] == '\n')
// 	// 	i++;
// 	ans = ft_strndup(line, i);
// 	return (free(line), ans);
// }

int	start_shell(char **temp_env)
{
	t_argtable	*arg_table;
	t_argtable	*temp_table;
	char		**cmd;

	while (1)
	{
		cmd = ft_split_c(ft_add_ifsp_nosp(get_from_readline()), ' ');
		replace_variable(cmd, temp_env, g_pi);
		if (!check_heredoc(cmd) && cmd[0])
		{
			arg_table = create_table(&cmd, temp_env);
			temp_table = arg_table;
			if ((!ft_strcmp(arg_table->cmd, "cd")
					|| check_builtin(&arg_table, temp_env)) && arg_table->next)
				temp_table = arg_table->next;
			else if (!ft_strcmp(temp_table->cmd, "cd") && !temp_table->next)
				chang_directory(temp_table->argv[1], temp_env);
			else if (check_char_sptable(temp_table))
				g_pi = pipex(&temp_table, temp_env);
			free_all_table(arg_table);
		}
		free_s(NULL, cmd);
	}
	free_chardstar(temp_env);
}

int	check_char_sptable(t_argtable *arg_table)
{
	int	i;

	i = 0;
	while (arg_table->redirection[i])
	{
		if (!ft_strcmp(arg_table->redirection[i], "infile")
			&& check_spcharactor(arg_table->infile))
			return (0);
		else if (!ft_strcmp(arg_table->redirection[i], "outfile")
			&& check_spcharactor(arg_table->outfile))
			return (0);
		else if (!ft_strcmp(arg_table->redirection[i], "append")
			&& check_spcharactor(arg_table->appendfile))
			return (0);
		else if (!ft_strcmp(arg_table->redirection[i], "heredoc")
			&& check_spcharactor(arg_table->heredoc_kw))
			return (0);
		i++;
	}
	if (arg_table->next)
		return (check_char_sptable(arg_table->next));
	else
		return (1);
}

int	check_spcharactor(char *str)
{
	if (!str || str[0] == '>' || str[0] == '<' || str[0] == '|'
		|| str[0] == ';' || str[0] == '&' || str[0] == '#' || str[0] == '-'
		|| str[0] == '(' || str[0] == ')')
	{
		write(2, "Syntax error near unexpected token: '", 37);
		if (str)
			write (2, str, ft_strlen(str));
		write(2, "'\n", 2);
		return (1);
	}
	return (0);
}

int	check_heredoc(char **cmd)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], "<<"))
		{
			if (!cmd[i + 1] || !ft_strcmp(cmd[i + 1], "|")
				|| !ft_strcmp(cmd[i + 1], "<")
				|| !ft_strcmp(cmd[i + 1], ">") || !ft_strcmp(cmd[i + 1], ">>"))
			{
				write(2, "Syntax error near unexpected token: ''\n", 39);
				status = 1;
			}
		}
		i++;
	}
	return (status);
}
