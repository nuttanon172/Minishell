/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:24:59 by ntairatt          #+#    #+#             */
/*   Updated: 2023/11/06 10:51:46 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_atoi(char *nbr)
{
	int		ans;
	char	*temp;

	temp = nbr;
	ans = 0;
	while (*temp && (*temp < '0' || *temp > '9'))
		temp++;
	while (*temp && *temp >= '0' && *temp <= '9')
	{
		ans = (10 * (ans) + (*temp - '0'));
		temp++;
	}
	return (ans);
}

void	free_chardstar(char **path)
{
	int	i;

	i = 0;
	if (!path)
		return ;
	while (path[i])
	{
		free(path[i]);
		path[i++] = NULL;
	}
	free(path);
	path = NULL;
}

void	free_re_arg(t_argtable **temp)
{
	t_keyword	*kwtemp;

	free_chardstar((*temp)->redirection);
	free_chardstar((*temp)->argv);
	while ((*temp)->heredoc_kw)
	{
		kwtemp = ((*temp)->heredoc_kw);
		(*temp)->heredoc_kw = (*temp)->heredoc_kw->next;
		free(kwtemp);
	}
}
