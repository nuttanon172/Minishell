/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_0main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:13:30 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/07 11:09:01 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		pi;
	char	first_dir[4096];

	(void)argc;
	(void)argv;
	pi = 0;
	getcwd(first_dir, sizeof(first_dir));
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	write_env(envp, first_dir);
	pi = start_shell(pi, first_dir);
	return (pi);
}

int	start_shell(int pi, char *first_dir)
{
	char		**cmd;
	t_argtable	*arg_table;
	char		**temp_env;
	t_argtable	*temp_table;

	while (1)
	{
		temp_env = ft_splitenv(first_dir);
		cmd = ft_split_c(ft_add_ifsp_nosp(get_from_readline()), ' ');
		replace_variable(cmd, temp_env, pi);
		if (!check_heredoc(cmd) && cmd[0])
		{
			arg_table = create_table(&cmd, temp_env);
			temp_table = arg_table;
			if (!ft_strcmp(arg_table->cmd, "cd") && arg_table->next)
				temp_table = arg_table->next;
			else if (!ft_strcmp(temp_table->cmd, "cd") && !temp_table->next)
				chang_directory(temp_table->argv[1]);
			else if (check_char_sptable(temp_table))
				pi = pipex(&temp_table, temp_env);
			free_all_table(arg_table);
		}
		free_s(NULL, cmd, temp_env);
	}
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
	return (1);
}

int	check_spcharactor(char *str)
{
	if (!str || str[0] == '>' || str[0] == '<' || str[0] == '|'
		|| str[0] == ';' || str[0] == '&' || str[0] == '#' || str[0] == '-'
		|| str[0] == '(' || str[0] == ')')
	{
		write (2, "Syntax error near unexpected token: '", 37);
		if (str)
			write (2, str, ft_strlen(str));
		write (2, "'\n", 2);
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
				write (2, "Syntax error near unexpected token: ''\n", 39);
				status = 1;
			}
		}
		i++;
	}
	return (status);
}
