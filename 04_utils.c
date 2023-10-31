/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:46:36 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/31 17:56:15 by ntairatt         ###   ########.fr       */
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
		printf("\nCurrent directory: %s\n", getcwd(NULL, 0));
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_pi = 130;
	}
}
