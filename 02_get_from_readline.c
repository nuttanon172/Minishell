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

char	*get_from_readline(void)
{
	char	*line;
	int		signal;
	char	str[4096];
	char	*dir;

	signal = 0;
	dir = NULL;
	getcwd(str, sizeof(str));
	dir = ft_strcat(ft_strcat(
				ft_strdup("\033[0;34mCurrent directory: "), ft_strdup(str)),
			ft_strdup("\nWelcome to my world my rule $ "));
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

char	*ft_strcat(char *src, char *dst)
{
	char	*ans;
	size_t	count;
	size_t	i;
	size_t	j;

	if (!dst && !src)
		return (NULL);
	if (!dst || !*dst)
		return (src);
	else if (!src || !*src)
		return (dst);
	count = ft_strlen(src) + ft_strlen(dst);
	ans = (char *)malloc(sizeof(char) * (count + 1));
	if (!ans)
		return (NULL);
	i = 0;
	j = 0;
	while (src[j])
		ans[i++] = src[j++];
	j = 0;
	while (dst[j])
		ans[i++] = dst[j++];
	ans[i] = '\0';
	return (free(src), free(dst), ans);
}
