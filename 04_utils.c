/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:46:36 by ntairatt          #+#    #+#             */
/*   Updated: 2023/11/01 11:16:47 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig_number)
{
	char	*str;

	(void)sig_number;
	str = getenv("SHLVL");
	if (ft_atoi(str) == 1)
	{
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	g_pi = 130;
}
