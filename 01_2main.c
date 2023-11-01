/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_2main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchulkai <vchulkai@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:27:46 by ntairatt          #+#    #+#             */
/*   Updated: 2023/11/01 18:29:11 by vchulkai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_util(t_argtable **temp, char **cmd)
{
	int	i;

	i = count_command_arg(cmd);
	(*temp)->argv = (char **)malloc(sizeof(char *) * (i + 1));
	if ((*temp)->argv)
		(*temp)->argv[i] = NULL;
	i = count_redirection(cmd);
	(*temp)->redirection = (char **)malloc(sizeof(char *) * (i + 1));
	if ((*temp)->redirection)
		(*temp)->redirection[i] = NULL;
	(*temp)->next = NULL;
	(*temp)->cmd = NULL;
	(*temp)->heredoc_kw = NULL;
	(*temp)->infile = NULL;
	(*temp)->outfile = NULL;
	(*temp)->appendfile = NULL;
}

void	initialize_data_table(t_argtable **temp, char **cmd)
{
	if ((*temp))
	{
		(*temp)->next = (t_argtable *)malloc(sizeof(t_argtable));
		if (!(*temp)->next)
			return ;
		(*temp) = (*temp)->next;
	}
	else if (!(*temp))
	{
		(*temp) = (t_argtable *)malloc(sizeof(t_argtable));
		if (!*temp)
			return ;
		(*temp)->next = NULL;
	}
	init_util(temp, cmd);
}

int	count_command_arg(char **cmd)
{
	int		i;
	size_t	j;

	if (!cmd || !*cmd)
		return (0);
	i = 0;
	j = 0;
	while (cmd[j] && ft_strcmp(cmd[j], "|") && ft_strcmp(cmd[j], "||"))
	{
		if (!ft_strcmp(cmd[j], "<") || !ft_strcmp(cmd[j], "<<")
			|| !ft_strcmp(cmd[j], ">") || !ft_strcmp(cmd[j], ">>"))
			j++;
		else
			i++;
		if (cmd[j])
			j++;
	}
	return (i);
}

int	count_redirection(char **cmd)
{
	size_t	j;
	int		i;

	if (!cmd || !*cmd)
		return (0);
	j = 0;
	i = 0;
	while (cmd[j] && ft_strcmp(cmd[j], "|") && ft_strcmp(cmd[j], "||"))
	{
		if (!ft_strcmp(cmd[j], "<") || !ft_strcmp(cmd[j], "<<")
			|| !ft_strcmp(cmd[j], ">") || !ft_strcmp(cmd[j], ">>"))
			i++;
		j++;
	}
	return (i);
}

void	replace_variable(char **cmd, char **env, int pi)
{
	bool	is_insq;
	bool	is_indq;
	int		*i;

	is_indq = false;
	is_insq = false;
	i = (int *)malloc(sizeof(int) * 2);
	if (!i)
		return ;
	i[0] = 0;
	i[1] = 0;
	while (cmd[i[0]])
	{
		check_inq(cmd[i[0]][i[1]], &is_indq, &is_insq);
		if ((!is_insq && cmd[i[0]][i[1]] == '$'))
			sub_replace_veriable(cmd, &i, pi, env);
		if ((i[1] <= (int)ft_strlen(cmd[i[0]])) && cmd[i[0]][i[1]])
			i[1]++;
		else
		{
			i[0]++;
			i[1] = 0;
		}
	}
	free(i);
}
