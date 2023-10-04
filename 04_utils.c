/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchulkai <vchulkai@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:27:14 by lbhuprad          #+#    #+#             */
/*   Updated: 2023/10/04 16:21:02 by vchulkai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int sig_number)
{
	(void)sig_number;
	printf("\nCurrent directory: %s\n", getcwd(NULL, 0));
	rl_on_new_line();
	rl_redisplay();
	signal(SIGINT, sig_handler);
	return ;
}

void	sig_handler1(int sig_number)
{

	printf("in siguser\n");
	exit(0);
	return;
}