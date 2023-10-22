/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_1main_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:35:26 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/22 22:32:27 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_path_util(char *argv)
{
	if (ft_strcmp(argv, "cd"))
	{
		write(2, argv, ft_strlen(argv));
		write(2, ": Command not found\n", 20);
	}
}

void	free_re_arg(t_argtable **temp)
{
	free_chardstar((*temp)->redirection);
	free_chardstar((*temp)->argv);
}
