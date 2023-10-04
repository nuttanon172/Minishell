/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_utils_table_ok.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchulkai <vchulkai@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:28:39 by lbhuprad          #+#    #+#             */
/*   Updated: 2023/09/30 00:48:11 by vchulkai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_argtable	*create_table(char ***cmda, char **first_dir)
{
	t_table		s;

	set_int_zero(&s);
	s.cmd = *cmda;
	s.arg_table = NULL;
	s.temp = NULL;
	initialize_data_table(&(s.arg_table), s.cmd);
	s.temp = s.arg_table;
	while (s.cmd[s.i] != NULL)
	{
		if (s.cmd[s.i] && (!ft_strcmp(s.cmd[s.i], "<")
				|| !ft_strcmp(s.cmd[s.i], "<<")
				|| !ft_strcmp(s.cmd[s.i], ">") || !ft_strcmp(s.cmd[s.i], ">>")))
		{
			create_table_redirect(&(s.temp), s.cmd, &(s.i), &(s.k));
		}
		else if (!ft_strcmp(s.cmd[s.i], "|") || !ft_strcmp(s.cmd[s.i], "||"))
			s.i += create_table_pipe_or(&(s.temp), &(s.j), &(s.k), s.cmd + s.i);
		else if (s.cmd[s.i])
		{
			if (!s.temp->cmd) 
				s.temp->cmd = get_path(replace_q(ft_strdup(s.cmd[s.i])), first_dir);
			if (ft_strcmp(s.temp->cmd, "cd"))
				s.temp->argv[s.j++] = get_command(replace_q(ft_strdup(s.cmd[s.i++])));
			else
				s.temp->argv[s.j++] = replace_q(ft_strdup(s.cmd[s.i++]));
		}
	}
	return (s.arg_table);
}

void	set_int_zero(t_table *s)
{
	(*s).i = 0;
	(*s).j = 0;
	(*s).k = 0;
}

void	free_all_table(t_argtable *arg_table)
{
	t_argtable	*temp;
	t_argtable	*temp2;

	temp = arg_table;
	while (temp)
	{
		free(temp->cmd);
		if (temp->appendfile)
		{
			free(temp->appendfile);
			temp->appendfile = NULL;
		}
		if (temp->infile)
		{
			free(temp->infile);
			temp->infile = NULL;
		}
		if (temp->outfile)
		{
			free(temp->outfile);
			temp->outfile = NULL;
		}
		if (temp->heredoc_kw)
		{
			free(temp->heredoc_kw);
			temp->heredoc_kw = NULL;
		}
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

int	create_table_pipe_or(t_argtable **arg_table, int *j, int *k, char **cmd)
{
	t_argtable	**temp;
	char		**cmds;

	temp = arg_table;
	cmds = cmd;
	if ((*temp)->cmd && !ft_strcmp(*cmds, "||"))
	{
		initialize_data_table(temp, cmds);
		(*temp)->cmd = ft_strdup("or");
	}
	cmds++;
	*j = 0;
	*k = 0;
	initialize_data_table(temp, cmds);
	return(1);
}

