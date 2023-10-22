/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_0utils_table_ok.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchulkai <vchulkai@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:15:04 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/20 04:53:30 by vchulkai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rep_q(char *cmd)
{
	return (replace_q(ft_strdup(cmd)));
}

t_argtable	*create_table(char ***cmda, char **first_dir)
{
	t_table		s;

	set_int_zero(&s);
	s.cmd = *cmda;
	initialize_data_table(&(s.arg_table), s.cmd);
	s.temp = s.arg_table;
	while (s.cmd[s.i] != NULL)
	{
		if (s.cmd[s.i] && (!ft_strcmp(s.cmd[s.i], "<") || \
			!ft_strcmp(s.cmd[s.i], "<<") || \
			!ft_strcmp(s.cmd[s.i], ">") || !ft_strcmp(s.cmd[s.i], ">>")))
			create_table_redirect(&(s.temp), s.cmd, &(s.i), &(s.k));
		else if (!ft_strcmp(s.cmd[s.i], "|") || !ft_strcmp(s.cmd[s.i], "||"))
			s.i += create_table_pipe_or(&(s.temp), &(s.j), &(s.k), s.cmd + s.i);
		else if (s.cmd[s.i])
		{
			if (!s.temp->cmd)
				s.temp->cmd = get_path(rep_q(s.cmd[s.i]), first_dir);
			s.temp->argv[s.j++] = replace_q(ft_strdup(s.cmd[s.i++]));
		}
	}
	return (s.arg_table);
}

void	free_argtable(t_argtable *temp)
{
	free(temp->cmd);
	if (temp->appendfile)
		free_null(temp->appendfile);
	if (temp->infile)
		free_null(temp->infile);
	if (temp->outfile)
		free_null(temp->outfile);
	if (temp->heredoc_kw)
		free_null(temp->heredoc_kw);
}

void	free_all_table(t_argtable *arg_table)
{
	t_argtable	*temp;
	t_argtable	*temp2;

	temp = arg_table;
	while (temp)
	{
		free_argtable(temp);
		free_re_arg(&temp);
		if (!temp->next)
		{
			free(temp);
			break ;
		}
		temp2 = temp;
		temp = temp->next;
		free(temp2);
		temp2 = NULL;
	}
	arg_table = NULL;
}

void	create_table_redirect(t_argtable **arg_table,
			char **cmd, int *i, int *k)
{
	(*arg_table)->redirection[(*k)++] = replace_q(return_lebel(cmd[*i]));
	if (!ft_strcmp(cmd[*i], ">") && cmd[*i + 1])
		(*arg_table)->outfile = replace_q(ft_strdup(cmd[*i + 1]));
	else if (!ft_strcmp(cmd[*i], ">>") && cmd[*i + 1])
		(*arg_table)->appendfile = replace_q(ft_strdup(cmd[*i + 1]));
	else if (!ft_strcmp(cmd[*i], "<") && cmd[*i + 1])
		(*arg_table)->infile = replace_q(ft_strdup(cmd[*i + 1]));
	else if (!ft_strcmp(cmd[*i], "<<") && cmd[*i + 1])
		(*arg_table)->heredoc_kw = replace_q(ft_strdup(cmd[*i + 1]));
	if (cmd[++(*i)])
		(*i)++;
}
