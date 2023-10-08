/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_1utils_env_split_ok.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:42:56 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/08 14:45:42 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_split_c(char *string, char ch)
{
	char	**ans;
	char	*temp;
	int		i;

	i = 0;
	temp = string;
	if (temp == NULL)
		return (NULL);
	while (*temp == ' ')
		temp++;
	ans = (char **)malloc(sizeof(char *) * (ft_csp(temp, ch) + 2));
	while (i <= ft_csp(string, ch))
	{
		if (ft_counttochar(temp, ch) != -1)
		{
			ans[i++] = ft_strndup(temp, ft_counttochar(temp, ch));
			temp = temp + ft_counttochar(temp, ch) + 1;
			while (*temp == ch)
				temp++;
		}
		else
			ans[i++] = ft_strndup(temp, ft_strlen(temp));
	}
	ans[i] = NULL;
	return (free(string), ans);
}

int	ft_csp(char *src, char ch)
{
	int		i;
	bool	is_insq;
	bool	is_indq;
	char	*temp;

	is_insq = false;
	is_indq = false;
	i = 0;
	temp = src;
	while (*temp)
	{
		if (!is_insq && *temp == '\"')
			is_indq = !is_indq;
		else if (!is_indq && *temp == '\'')
			is_insq = !is_insq;
		if (*temp == ch && *(temp + 1) != ch && !is_indq && !is_insq)
			i++;
		temp++;
	}
	return (i);
}

char	*ft_getenv(char **env, char	*var)
{
	int		i;
	char	*ans;
	char	*temp;

	i = 0;
	while (env[i])
	{
		temp = env[i];
		if (!ft_strncmp(temp, var, ft_strlen(var)))
		{
			temp = temp + ft_strlen(var);
			if (*temp == '=')
			{
				temp = temp + 1;
				ans = ft_strdup(temp);
			}
		}
		i++;
	}
	free(var);
	return (ans);
}

int	count_newline(char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == '\n')
			j++;
		i++;
	}
	return (j);
}
