/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_0pipex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:07:48 by vchulkai          #+#    #+#             */
/*   Updated: 2023/10/27 10:56:58 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipex(t_argtable **arg_table, char **first_dir)
{
	t_argtable	**temp;
	pid_t		pid;
	int			status;

	temp = arg_table;
	if (!ft_strcmp((*temp)->argv[0], "exit") && !(*temp)->next)
		execve((*temp)->cmd, (*temp)->argv, first_dir);
	pid = fork();
	if (!pid)
		exit(execve_command(temp, first_dir));
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
	{
		defualt_input(temp, pipeid[1]);
		if (ft_strcmp((*temp)->argv[0], "minishell")
			&& ft_strcmp((*temp)->argv[0], "./minishell"))
			dup2_and_close(pipeid[0], pipeid[1], STDOUT_FILENO);
		if (!(*temp)->argv[1])
			isdir((*temp)->cmd);
		if (!check_builtin(temp, &first_dir))
			execve((*temp)->cmd,(*temp)->argv, first_dir);
		return (close(pipeid[1]), exit(127), 1);
	}
	waitpid(pid, &status, 0);
	dup2_and_close(pipeid[1], pipeid[0], STDIN_FILENO);
	j = -1;
	j = sub_exec_redirect(temp, pipeid[0], first_dir);
	close(pipeid[0]);
	if (j >= 0)
		return (j);
	else
		return (WEXITSTATUS(status));
}

int	check_builtin(t_argtable **temp, char ***envp)
{
	if (!(*temp)->cmd)
		return (1);
	if (!ft_strcmp((*temp)->cmd, "unset"))
		ft_unset(*envp, (*temp)->argv);
	else if (!ft_strcmp((*temp)->cmd, "export"))
		*envp = ft_export(*envp, (*temp)->argv);
	else
		return (0);
	return (1);
}

int	sub_exec_redirect(t_argtable **temp, int pipeid, char **first_dir)
{
	size_t	i;

	i = 0;
	while ((*temp)->redirection[i])
	{
		if (!ft_strncmp((*temp)->redirection[i], "outfile", 7)
			|| !ft_strncmp((*temp)->redirection[i], "append", 6))
		{
			sub_exec_redirect_loop(temp, i, pipeid);
			break ;
		}
		i++;
	}
	if (!(*temp)->outfile && !(*temp)->next)
		print_file_des(pipeid, NULL, 0);
	while ((*temp)->next)
	{
		(*temp) = (*temp)->next;
		if (!access(".input_file", F_OK))
			unlink(".input_file");
		if (!access(".input_file", F_OK))
			unlink(".input_file");
		if (!ft_strcmp((*temp)->argv[0], "minishell"))
			break ;
		return (execve_command(temp, first_dir));
	}
	return (-1);
}

void	sub_exec_redirect_loop(t_argtable **temp, int i, int pipeid)
{
	if (!ft_strncmp((*temp)->redirection[i], "outfile", 7)
		|| !ft_strncmp((*temp)->redirection[i], "append", 6))
	{
		if (!ft_strncmp((*temp)->redirection[i], "outfile", 7)
			&& (*temp)->appendfile)
		{
			close(open((*temp)->outfile, O_CREAT | O_WRONLY
					| O_TRUNC, 0777));
			print_file_des(pipeid, (*temp)->appendfile, 'a');
		}
		else if (!ft_strncmp((*temp)->redirection[i], "append", 6)
			&& (*temp)->outfile)
		{
			close(open((*temp)->appendfile, O_CREAT | O_WRONLY
					| O_TRUNC, 0777));
			print_file_des(pipeid, (*temp)->outfile, 'o');
		}
		if (!ft_strncmp((*temp)->redirection[i], "outfile", 7))
			print_file_des(pipeid, (*temp)->outfile, 'o');
		else if (!ft_strncmp((*temp)->redirection[i], "append", 6))
			print_file_des(pipeid, (*temp)->appendfile, 'a');
	}
}
