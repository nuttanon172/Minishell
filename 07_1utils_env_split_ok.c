/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_1utils_env_split_ok.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:42:56 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/12 13:04:09 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_split_utils(char **ans, char *string, char *temp, char ch)
{
	size_t	i;

	i = 0;
	while (i <= (size_t)ft_csp(string, ch))
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
}

char	**ft_split_c(char *string, char ch)
{
	char	**ans;
	char	*temp;

	temp = string;
	if (temp == NULL)
		return (NULL);
	while (*temp == ' ')
		temp++;
	ans = (char **)malloc(sizeof(char *) * (ft_csp(temp, ch) + 2));
	if (!ans)
		return (NULL);
	ft_split_utils(ans, string, temp, ch);
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
	size_t		i;
	char	*ans;
	char	*temp;

	i = 0;
	ans = NULL;
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
