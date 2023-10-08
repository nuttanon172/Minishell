/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:27:14 by lbhuprad          #+#    #+#             */
/*   Updated: 2023/10/08 09:51:09 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig_number)
{
	if (sig_number == SIGINT)
	{
		printf("\nCurrent directory: %s\n", getcwd(NULL, 0));
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
