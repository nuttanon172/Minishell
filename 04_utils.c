/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:46:36 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/09 16:46:41 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig_number)
{
	(void)sig_number;
	printf("\nCurrent directory: %s\n", getcwd(NULL, 0));
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
