/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_unset_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:02:09 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/07 17:05:41 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unset.h"

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
			ans[i++] = ft_strdup(temp);
			temp = temp + ft_counttochar(temp, ch) + 1;
			while (*temp == ch)
				temp++;
		}
		else
			ans[i++] = ft_strdup(temp);
	}
	ans[i] = NULL;
	return (ans);
}

char	**ft_splitenv(void)
{
	struct stat	st;
	char		*string;
	int			fd;
	char		**envp;

	fd = open(".minishell.env", O_RDONLY);
	stat(".minishell.env", &st);
	if (!st.st_size)
		return (NULL);
	string = (char *)malloc(sizeof(char) * (st.st_size) + 1);
	string[st.st_size] = '\0';
	read(fd, string, st.st_size);
	envp = ft_split_c(string, '\n');
	close(fd);
	free(string);
	return (envp);
}
