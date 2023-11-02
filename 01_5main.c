/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_5main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchulkai <vchulkai@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 00:07:49 by vchulkai          #+#    #+#             */
/*   Updated: 2023/11/02 00:13:36 by vchulkai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_char_sptable_util(t_argtable *arg_table, int i)
{
	if (!ft_strcmp(arg_table->redirection[i], "infile")
		&& check_spcharactor(arg_table->infile))
		return (0);
	else if (!ft_strcmp(arg_table->redirection[i], "outfile")
		&& check_spcharactor(arg_table->outfile))
		return (0);
	else if (!ft_strcmp(arg_table->redirection[i], "append")
		&& check_spcharactor(arg_table->appendfile))
		return (0);
	return (1);
}
