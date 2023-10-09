/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_4main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:26:29 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/09 15:57:39 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_in_q(char c, bool *is_indq, bool *is_insq)
{
	if (c == '\"')
		*is_indq = !(*is_indq);
	if (!is_indq && c == '\'')
		*is_insq = !(*is_insq);
}

int	count_special_character(char *command)
{
	int		i;
	bool	is_indq;
	bool	is_insq;
	char	*t;

	i = 0;
	t = command;
	is_indq = false;
	is_insq = false;
	while (*t)
	{
		if (*t == '\"')
			is_indq = !is_indq;
		if (!is_indq && *t == '\'')
			is_insq = !is_insq;
		if (!is_indq && !is_insq && (*t == '|' || *t == '<' || *t == '>'))
		{
			while ((*t == '>' && *(t + 1) == '>')
				|| (*t == '<' && *(t + 1) == '<'))
				t++;
			i++;
		}
		t++;
	}
	return (i);
}

void	clear_q(char **cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		cmd[i] = replace_q(cmd[i]);
		i++;
	}
}

char	*replace_q(char *cmd)
{
	char	*ans;
	bool	is_indq;
	bool	is_insq;
	int		i;
	int		j;

	i = 0;
	j = 0;
	is_indq = false;
	is_insq = false;
	ans = (char *)malloc(ft_strlen(cmd) - count_qoute(cmd) + 1);
	if (!ans)
		return (NULL);
	while (cmd[i])
	{
		if (!is_insq && cmd[i] == '\"')
			is_indq = !is_indq;
		else if (!is_indq && cmd[i] == '\'')
			is_insq = !is_insq;
		else
			ans[j++] = cmd[i];
		i++;
	}
	ans[j] = '\0';
	return (free(cmd), ans);
}

int	count_qoute(char *cmd)
{
	bool	is_indq;
	bool	is_insq;
	char	*temp;
	int		i;

	is_indq = false;
	is_insq = false;
	temp = cmd;
	i = 0;
	while (*temp)
	{
		if ((!is_insq && *temp == '\"') || (is_indq && *temp == '\''))
		{
			if (!is_insq && *temp == '\"')
				is_indq = !is_indq;
			if (!is_indq && *temp == '\'')
				is_insq = !is_insq;
			i++;
		}
		else if ((!is_indq && !is_insq) && (*temp == '\'' || *temp == '\"'))
			i++;
		temp++;
	}
	return (i);
}
