/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_0main_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:59:24 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/06 19:20:16 by ntairatt         ###   ########.fr       */
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

void	start_shell_util(char **temp_env, char *command, char **check)
{
	command = get_from_readline(temp_env);
	if (*command)
		add_history(command);
	command = ft_add_ifsp_nosp(command);
	check = ft_split_c(command, ' ');
}
