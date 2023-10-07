/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:10:12 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/07 21:40:38 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

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

char	*ft_strndup(char *src, int n)
{
	char	*ans;

	ans = NULL;
	if (!*src || n == 0)
		return (NULL);
	if (ft_strlen(src) < (size_t)n)
		n = ft_strlen(src);
	ans = (char *)malloc(sizeof(char) * (n + 1));
	ans[n--] = '\0';
	while (n >= 0)
	{
		ans[n] = src[n];
		n--;
	}
	return (ans);
}
