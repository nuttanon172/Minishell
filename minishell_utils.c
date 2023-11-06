/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:45:33 by ntairatt          #+#    #+#             */
/*   Updated: 2023/11/06 15:46:43 by ntairatt         ###   ########.fr       */
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

void	chang_directory(char *path, char **env)
{
	char	str[4096];
	char	*previous;
	char	**temp;
	char	*home;

	temp = env;
	getcwd(str, sizeof(str));
	find_home_old(&previous, &home, temp);
	if (!path)
		chdir(home);
	else if (!ft_strcmp(path, "-"))
		chdir(previous);
	else if (!access(path, F_OK))
		chdir(path);
	while (*temp)
	{
		if (!ft_strncmp(*temp, "OLDPWD=", 7))
			*temp = ft_strcat(ft_strdup("OLDPWD="), ft_strdup(str));
		temp++;
	}
	free(previous);
	free(home);
	free(*temp);
}

void	find_home_old(char **previous, char **home, char **temp)
{
	char	**chars;

	chars = temp;
	*previous = ft_getenv(temp, ft_strdup("OLDPWD"));
	*home = ft_getenv(temp, ft_strdup("HOME"));
}
