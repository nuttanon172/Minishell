/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_2main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:27:46 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/06 18:53:49 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*return_lebel(char *c)
{
	if (!ft_strcmp(c, ">"))
		return (ft_strdup("outfile"));
	if (!ft_strcmp(c, ">>"))
		return (ft_strdup("append"));
	if (!ft_strcmp(c, "<"))
		return (ft_strdup("infile"));
	if (!ft_strcmp(c, "<<"))
		return (ft_strdup("heredoc"));
	return (NULL);
}

void	initialize_data_table(t_argtable **temp, char **cmd)
{
	int	i;

	if ((*temp))
	{
		(*temp)->next = (t_argtable *)malloc(sizeof(t_argtable));
		(*temp) = (*temp)->next;
	}
	else if (!(*temp))
	{
		(*temp) = (t_argtable *)malloc(sizeof(t_argtable));
		(*temp)->next = NULL;
	}
	i = count_command_arg(cmd);
	(*temp)->argv = (char **)malloc(sizeof(char *) * (i + 1));
	(*temp)->argv[i] = NULL;
	i = count_redirection(cmd);
	(*temp)->redirection = (char **)malloc(sizeof(char *) * (i + 1));
	(*temp)->redirection[i] = NULL;
	(*temp)->next = NULL;
	(*temp)->cmd = NULL;
	(*temp)->heredoc_kw = NULL;
	(*temp)->infile = NULL;
	(*temp)->outfile = NULL;
	(*temp)->appendfile = NULL;
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
	char	**temp;
	size_t	j;
	int		i;

	if (!cmd || !*cmd)
		return (0);
	temp = cmd;
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
	i = malloc(sizeof(int) * 2);
	i[0] = 0;
	i[1] = 0;
	while (cmd[i[0]])
	{
		check_inq(cmd[i[0]][i[1]], &is_indq, &is_insq);
		if (!is_insq && cmd[i[0]][i[1]] == '$')
			sub_replace_veriable(cmd, &i, pi, env);
		if (cmd[i[0]][i[1]])
			i[1]++;
		else
		{
			i[0]++;
			i[1] = 0;
		}
	}
	free(i);
}
