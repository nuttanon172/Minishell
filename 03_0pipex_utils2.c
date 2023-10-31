/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_0pipex_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:11:45 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/31 18:12:32 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		sub_util();
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
