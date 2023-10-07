/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_0main_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:59:24 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/07 11:00:04 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_s(char *command, char **check, char **temp_env)
{
	if (command)
		free(command);
	if (check)
		free_chardstar(check);
	if (temp_env)
		free_chardstar(temp_env);
	wait(NULL);
	if (!access(".here_doc", F_OK))
		unlink(".here_doc");
	if (!access(".input_file", F_OK))
		unlink(".input_file");
}
