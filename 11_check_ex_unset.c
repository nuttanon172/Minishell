/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_check_ex_unset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchulkai <vchulkai@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:50:06 by vchulkai          #+#    #+#             */
/*   Updated: 2023/10/25 22:10:07 by vchulkai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printerror(char *cmd, char *command)
{
	write(2, "minishell: ", 11);
	write(2, command, ft_strlen(command));
	write(2, ": '", 3);
	write(2, cmd, ft_strlen(cmd));
	write(2, "': not a valid identifier\n", 26);
}

int	check_ex_unset(char *argv, char *cmd)
{
	char	*temp;

	temp = argv;
	if (ft_csp(argv, '=') > 1 || (argv[0] >= '0' && argv[0] <= '9') \
		|| argv[0] == '=')
		return (printerror(argv, cmd), 0);
	while (*temp)
	{
		if (*temp >= 'a' && *temp <= 'z')
			temp++;
		else if (*temp >= 'A' && *temp <= 'Z')
			temp++;
		else if (*temp == '_')
			temp++;
		else
			break ;
	}
	if (*temp == '=' || (!*temp && !ft_strcmp(cmd, "unset")))
		return (1);
	else if (*temp == '+' && *(temp + 1) == '=' && !ft_strcmp(cmd, "export"))
		return (1);
	else if (!*temp)
		return (0);
	else
		return (printerror(argv, cmd), 0);
}
