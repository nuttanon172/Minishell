/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_0pipex_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 22:25:05 by ntairatt          #+#    #+#             */
/*   Updated: 2023/11/09 15:11:02 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	read_default_fd(t_argtable **arg_table, int pipeid)
{
	size_t	i;
	int		fd;
	char	*ans;

	i = 0;
	fd = 0;
	ans = NULL;
	while ((*arg_table)->redirection[i])
	{
		if (!ft_strcmp((*arg_table)->redirection[i], "heredoc"))
		{
			ans = ft_strcat(ans, here_doc((*arg_table)->heredoc_kw->kw));
			(*arg_table)->heredoc_kw = (*arg_table)->heredoc_kw->next;
		}
		else if (!ft_strcmp((*arg_table)->redirection[i], "infile") && fd == 0)
		{
			fd = -1;
			ans = ft_strcat(ans, open_inputdoc((*arg_table)->infile, pipeid));
		}
		i++;
	}
	fd = write_input_dummy(ans);
	ans = NULL;
	return (fd);
}

void	defualt_input(t_argtable **temp, int pipeid)
{
	int	fd;

	if ((*temp)->infile || (*temp)->heredoc_kw)
	{
		fd = read_default_fd(temp, pipeid);
		dup2_and_close(fd, fd, STDIN_FILENO);
	}
}

void	dup2_and_close(int closed, int new, int old)
{
	dup2(new, old);
	close(closed);
}

int	check_builtin(t_argtable **temp, char ***envp, int i)
{
	if (!(*temp)->cmd)
		return (1);
	if (!ft_strcmp((*temp)->cmd, "unset"))
		return (ft_unset(*envp, (*temp)->argv), 0);
	else if (!ft_strcmp((*temp)->cmd, "export"))
		return (ft_export(envp, (*temp)->argv), 0);
	else if (!ft_strcmp((*temp)->cmd, "echo") && i)
		return (ft_echo(&(*temp)->argv));
	else if (!ft_strcmp((*temp)->cmd, "pwd") && i)
		return (ft_pwd());
	else if (!ft_strcmp((*temp)->cmd, "exit"))
	{
		g_pi = ft_exit((*temp)->argv);
		return (0);
	}
	else if (!ft_strcmp((*temp)->cmd, "cd"))
		return (0);
	return (1);
}

void	sub_util(void)
{
	if (!access(".input_file", F_OK))
		unlink(".input_file");
	if (!access(".input_file", F_OK))
		unlink(".input_file");
}
