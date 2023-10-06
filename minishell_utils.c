/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:45:33 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/06 18:32:23 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_itoa(int nbr)
{
	long long		n;
	int				len;
	char			*result;

	n = nbr;
	len = 0;
	if (n == 0)
		len = 1;
	while (nbr)
	{
		nbr /= 10;
		len++;
	}
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (n == 0)
		result[0] = '0';
	while (n)
	{
		result[--len] = ((n % 10) + '0');
		n /= 10;
	}
	return (result);
}

void	free_chardstar(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		path[i++] = NULL;
	}
	free(path);
	path = NULL;
}

void	dup2_and_close(int closed, int new, int old)
{
	dup2(new, old);
	close(closed);
}

void	chang_directory(char *path)
{
	struct stat	s;

	if (stat(path, &s) == 0)
		chdir(path);
}
