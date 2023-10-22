/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_0main_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:59:24 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/22 22:22:57 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_s(char *command, char **check)
{
	if (command)
		free(command);
	if (check)
		free_chardstar(check);
	wait(NULL);
	if (!access(".here_doc", F_OK))
		unlink(".here_doc");
	if (!access(".input_file", F_OK))
		unlink(".input_file");
}
