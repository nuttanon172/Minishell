/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_1main_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:35:26 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/12 16:41:52 by ntairatt         ###   ########.fr       */
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
