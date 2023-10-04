/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:44:01 by naam              #+#    #+#             */
/*   Updated: 2023/10/04 18:43:13 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "export.h"

size_t	ft_strlen(const char *s)
{
	size_t	ct;

	if (!s)
		return (0);
	ct = 0;
	while (s[ct] != '\0')
		ct++;
	return (ct);
}

size_t	ft_arglen(char *argv)
{
	size_t	i;

	i = 0;
	while (argv[i] && argv[i] != '=')
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n) && ((s1[i] != '\0') || (s2[i] != '\0')))
	{
		if (s1[i] > s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] < s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
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

char	*ft_strdup(char *src)
{
	size_t	i;
	char	*ans;

	i = 0;
	ans = (char *)malloc(sizeof(char) * (ft_strlen(src) + 1));
	while (src[i])
	{
		ans[i] = src[i];
		i++;
	}
	ans[i] = '\0';
	return (ans);
}
