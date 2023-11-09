/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_get_from_readline.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:14:14 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/06 18:14:14 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**check_quote(int *signal, char **line, size_t *i, char what_quote)
{
	while (*signal != 0)
	{
		if (!(*line)[*i])
			*line = ft_strcat(*line, readline(">"));
		else
			(*i)++;
		if ((*line)[*i] == what_quote)
			*signal = !(*signal);
	}
	return (line);
}

void	get_from_readline_util(char	**line, int *signal)
{
	size_t	i;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\"' && *signal == 0)
			*signal = 1;
		line = check_quote(signal, line, &i, '\"');
		if ((*line)[i] == '\'' && *signal == 0)
			*signal = 1;
		line = check_quote(signal, line, &i, '\'');
		i++;
	}
}

char	*get_promt(char *str)
{
	char	*pwd;
	char	*promt;
	char	*status;

	pwd = ft_strcat(ft_strdup("\033[38;2;241;250;192mCurrent directory: "), \
		ft_strdup(str));
	status = ft_strcat(ft_itoa(g_pi), ft_strdup("$ "));
	promt = ft_strcat(ft_strdup("\n\033[38;2;44;221;13mminishell "), status);
	promt = ft_strcat(pwd, promt);
	return (promt);
}

char	*get_from_readline(void)
{
	char	*line;
	int		signal;
	char	str[4096];
	char	*dir;

	signal = 0;
	dir = NULL;
	getcwd(str, sizeof(str));
	dir = get_promt(str);
	line = readline(dir);
	if (!line)
	{
		free(dir);
		exit(0);
	}
	free(dir);
	get_from_readline_util(&line, &signal);
	check_pipe_and_return_line(&line);
	if (*line)
		add_history(line);
	return (line);
}

void	check_pipe_and_return_line(char **line)
{
	int	i;

	i = 0;
	while (1)
	{
		i = ft_strlen((*line)) - 1;
		while (i >= 0 && (*line)[i] && i != 0 && ((*line)[i] == ' '
			|| (*line)[i] == '\t' || (*line)[i] == '\n' || (*line)[i] == '\v'
				|| (*line)[i] == '\f'))
			i--;
		if (i < 0 || (*line)[i] != '|')
			break ;
		else
			(*line) = ft_strcat((*line), readline("pipe>"));
	}
}
