/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_2utils_env_split_ok.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:23:08 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/09 16:24:52 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	count_to_newline(char *src)
{
	char	*temp;
	int		i;

	i = 0;
	temp = src;
	while (*temp)
	{
		if (*temp == '\n' || !*temp)
		{
			if (!*temp)
				i--;
			break ;
		}
		i++;
		temp++;
	}
	return (i);
}
