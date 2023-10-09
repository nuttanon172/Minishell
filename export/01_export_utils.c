/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:58:05 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/09 15:51:41 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*ft_strdup(char *src)
{
	size_t	i;
	char	*ans;

	i = 0;
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
