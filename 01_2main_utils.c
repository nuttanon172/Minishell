/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_2main_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchulkai <vchulkai@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:53:51 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/20 03:32:33 by vchulkai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_inq(char ch, bool *is_indq, bool *is_insq)
{
	if (ch == '\"')
	{
		*(is_indq) = !(*(is_indq));
	}
	if (!(*is_indq) && ch == '\'')
	{
		*(is_insq) = !(*(is_insq));
	}
}

char	*return_lebel(char *c)
{
	if (!ft_strcmp(c, ">"))
		return (ft_strdup("outfile"));
	if (!ft_strcmp(c, ">>"))
		return (ft_strdup("append"));
	if (!ft_strcmp(c, "<"))
		return (ft_strdup("infile"));
	if (!ft_strcmp(c, "<<"))
		return (ft_strdup("heredoc"));
	return (NULL);
}
