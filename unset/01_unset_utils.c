/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_unset_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:41:59 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/07 17:02:22 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unset.h"

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
	char	*ans;
	int		i;

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
