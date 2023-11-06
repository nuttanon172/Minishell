/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_0pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:07:48 by vchulkai          #+#    #+#             */
/*   Updated: 2023/11/06 18:22:01 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipex_util(t_argtable ***temp2, char **first_dir)
{
	t_argtable	**temp;

	temp = *temp2;
	if ((*temp)->next)
	{
		if (!fork())
			execve_command(&(*temp)->next, first_dir);
		wait(NULL);
		(*temp)->next = NULL;
	}
}

int	pipex(t_argtable **arg_table, char ***first_dir)
{
	t_argtable	**temp;
	pid_t		pid;
	int			status;

	temp = arg_table;
	if (!(*temp)->next && check_builtin(arg_table, first_dir, 0))
		return (g_pi);
	if (!ft_strcmp((*temp)->argv[0], "exit") && !(*temp)->next)
		ft_exit((*temp)->argv);
	pid = fork();
	if (!pid)
	{
		if (!ft_strcmp((*temp)->argv[0], "minishell"))
		{
			pipex_util(&temp, *first_dir);
			execve((*temp)->cmd, (*temp)->argv, *first_dir);
			exit(g_pi);
		}
		else
			exit(execve_command(temp, *first_dir));
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	execve_command(t_argtable **arg_table, char **first_dir)
{
	t_argtable	**temp;
	int			pipeid[2];
	pid_t		pid;
	int			status;
	int			j;

	status = 0;
	temp = arg_table;
	pipe(pipeid);
	pid = fork();
	if (!pid)
		child_process(temp, pipeid, &first_dir);
	if ((*temp)->heredoc_kw)
		waitpid(pid, &status, 0);
	dup2_and_close(pipeid[1], pipeid[0], STDIN_FILENO);
	j = sub_exec_redirect(temp, pipeid[0], first_dir);
	waitpid(pid, &status, 0);
	close(pipeid[0]);
	if (j >= 0)
		return (j);
	else
		return (WEXITSTATUS(status));
}

int	is_bin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (0);
	return (0);
}

int	child_process(t_argtable **temp, int pipeid[2], char ***first_dir)
{
	defualt_input(temp, pipeid[1]);
	if (ft_strlen((*temp)->argv[0]) >= 9)
	{
		if (ft_strcmp((*temp)->argv[0], "minishell"))
		{
			if (ft_strlen((*temp)->argv[0]) < 10 || ft_strcmp((*temp)->argv[0] \
				+ ft_strlen((*temp)->argv[0]) - 10, "/minishell"))
				dup2_and_close(pipeid[0], pipeid[1], STDOUT_FILENO);
		}
	}
	else
		dup2_and_close(pipeid[0], pipeid[1], STDOUT_FILENO);
	if (!(*temp)->argv[1] && !is_bin((*temp)->cmd))
		isdir((*temp)->cmd);
	if (!check_builtin(temp, first_dir, 1))
	{
		execve((*temp)->cmd, (*temp)->argv, *first_dir);
		return (close(pipeid[1]), exit(127), 1);
	}
	else
		return (close(pipeid[1]), exit(0), 1);
}
