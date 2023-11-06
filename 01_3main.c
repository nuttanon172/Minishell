/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_3main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:39:03 by ntairatt          #+#    #+#             */
/*   Updated: 2023/11/06 12:43:49 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sub_replace_veriable(char **cmd, int **i, int pi, char **env)
{
	int		k;
	char	*t;

	(*i)[1]++;
	k = 0;
	while (cmd[(*i)[0]][(*i)[1]] && cmd[(*i)[0]][(*i)[1]] != '\''
			&& cmd[(*i)[0]][(*i)[1]] != '\"' && cmd[(*i)[0]][(*i)[1]] != '?'
			&& cmd[(*i)[0]][(*i)[1]] != '$' && cmd[(*i)[0]][(*i)[1]] != ' ')
	{
		k++;
		(*i)[1]++;
	}
	t = ft_getenv(env, ft_strndup(cmd[(*i)[0]] + (*i)[1] - k, k));
	if (cmd[(*i)[0]][(*i)[1]] != '?')
		cmd[(*i)[0]] = ft_strcat(ft_strcat(ft_strndup(cmd[(*i)[0]], \
			(*i)[1] - k - 1), t), ft_strdup(cmd[(*i)[0]] + (*i)[1]));
	else if (cmd[(*i)[0]][(*i)[1]] == '?')
		cmd[(*i)[0]] = ft_strcat(ft_strcat(ft_strndup(cmd[(*i)[0]], (*i)[1]
						- 1), ft_strdup(ft_itoa(pi))), ft_strndup(cmd[(*i)[0]]
					+ (*i)[1] + 1, ft_strlen(cmd[(*i)[0]] + (*i)[1] + 1)));
}

int	ft_counttochar(char *src, char ch)
{
	char	*temp;
	int		i;
	bool	is_insq;
	bool	is_indq;

	is_insq = false;
	is_indq = false;
	i = 0;
	temp = src;
	if (*temp == ch)
		return (0);
	while (*temp && (*temp != ch || is_indq || is_insq))
	{
		if (!is_insq && *temp == '\"')
			is_indq = !is_indq;
		else if (!is_indq && *temp == '\'')
			is_insq = !is_insq;
		i++;
		temp++;
	}
	if (!*temp)
		return (-1);
	else
		return (i);
}

int	check_lex(char cmd)
{
	if (cmd == '|' || cmd == '<' || cmd == '>')
		return (1);
	else
		return (0);
}

char	*ft_add_ifsp_nosp(char *cmd)
{
	int		i;
	int		j;
	char	*ans;
	bool	is_indq;
	bool	is_insq;

	is_indq = false;
	is_insq = false;

	ans = (char *)malloc(ft_strlen(cmd) + count_special_character(cmd) * 2 + 3);
	if (!ans)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i] == ' ')
		i++;
	while (cmd[i])
	{
		is_in_q(cmd[i], &is_indq, &is_insq);
		if (!is_indq && !is_insq && check_lex(cmd[i]) && cmd[i + 1])
			add_space(&j, &i, &ans, &cmd);
		else
			ans[j++] = cmd[i++];
	}
	ans[j] = '\0';
	return (free(cmd), ans);
}

void	add_space(int *j, int *i, char **ans, char **cmd)
{
	int	t;

	t = 0;
	if (*j != 0)
		(*ans)[(*j)++] = ' ';
	while (((*cmd)[*i] == '|' || (*cmd)[*i] == '<' || (*cmd)[*i] == '>'))
	{
		t++;
		(*ans)[(*j)++] = (*cmd)[(*i)++];
		if ((*cmd)[*i] != (*cmd)[*i - 1] || t == 2)
			break ;
	}
	(*ans)[(*j)++] = ' ';
}
