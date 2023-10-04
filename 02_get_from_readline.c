/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_from_readline.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbhuprad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:16:10 by lbhuprad          #+#    #+#             */
/*   Updated: 2023/09/26 15:16:10 by lbhuprad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_from_readline(char **env)
{
	char	*line;
	int		signal;
	char	str[4096];
	char	*dir;
	int		i;

	i = 0;
	signal = 0;
	dir = NULL;
	getcwd(str, sizeof(str));
	dir = ft_strcat(ft_strcat(ft_strdup("\033[0;34mCurrent directory: "), ft_strdup(str)), ft_strdup("\nWelcome to my world my rule $ "));
	line = readline(dir);
	if (!line)
	{
		free(dir);
		exit(0);
	}
	free(dir);
	while (line[i])
	{
		if (line[i] == '\"' && signal == 0)
			signal = 1;
		line = check_quote(&signal, line, &i, '\"');
		if (line[i] == '\'' && signal == 0)
			signal = 1;
		line = check_quote(&signal, line, &i, '\'');
		i++;
	}
	check_pipe_and_return_line(&line);
	return (line);
}

void	check_pipe_and_return_line(char **line)
{
	int	i;

	i = 0;
	while (1)
	{
		i = ft_strlen((*line)) - 1;
		while ((*line)[i] && i != 0 && ((*line)[i] == ' ' || (*line)[i] == '\t'
					|| (*line)[i] == '\n' || (*line)[i] == '\v'
				|| (*line)[i] == '\f'))
			i--;
		if (i < 0 || (*line)[i] != '|')
			break ;
		else
			(*line) = ft_strcat((*line), readline("pipe>"));
	}
}

size_t	ft_strlen(const char *s)
{
	size_t	ct;

	if (!s || !*s)
		return (0);
	ct = 0;
	while (s[ct] != '\0')
		ct++;
	return (ct);
}

char	*ft_strcat(char *src, char *dst)
{
	char	*ans;
	char	*t;
	char	*s;
	char	*d;
	size_t	count;

	s = src;
	d = dst;
	if (!dst && !src)
		return (NULL);
	if (!dst || !*dst)
		return (src);
	else if (!src || !*src)
		return (dst);
	count = ft_strlen(src) + ft_strlen(dst);
	ans = malloc(sizeof(char) * (count + 1));
	ans[count] = '\0';
	t = ans;
	while (*s)
		*t++ = *s++;
	while (*d)
		*t++ = *d++;
	free(src);
	free(dst);
	// printf("ans:%s\n", ans);
	return (ans);
}

char	*check_quote(int *signal, char *line, int *i, char what_quote)
{
	while (*signal != 0)
	{
		if (!line[*i])
			line = ft_strcat(line, readline(">"));
		else
			(*i)++;
		if (line[*i] == what_quote)
			*signal = 0;
	}
	return (line);
}
