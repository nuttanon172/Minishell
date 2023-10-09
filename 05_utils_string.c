/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_utils_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 20:55:56 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/09 16:09:51 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(char *src, int n)
{
	char	*ans;

	ans = NULL;
	if (!*src || n == 0)
		return (NULL);
	if (ft_strlen(src) < (size_t)n)
		n = ft_strlen(src);
	ans = (char *)malloc(sizeof(char) * (n + 1));
	if (!ans)
		return (NULL);
	ans[n--] = '\0';
	while (n >= 0)
	{
		ans[n] = src[n];
		n--;
	}
	return (ans);
}

char	*ft_strdup(char *src)
{
	char	*ans;
	size_t	i;

	i = 0;
	ans = NULL;
	if (!src || !*src)
		return (NULL);
	ans = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!ans)
		return (NULL);
	while (src[i])
	{
		ans[i] = src[i];
		i++;
	}
	ans[i] = '\0';
	return (ans);
}

int	ft_strcmp(char *src, char *dst)
{
	char	*t_src;
	char	*t_dst;

	t_src = src;
	t_dst = dst;
	while (*t_src && *t_dst && *t_src == *t_dst)
	{
		t_src++;
		t_dst++;
	}
	return (*t_src - *t_dst);
}

int	ft_strncmp(char *src, char *cmp, size_t	n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (src[i] != cmp[i])
			return (src[i] - cmp[i]);
		i++;
	}
	return (0);
}
