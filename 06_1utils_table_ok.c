/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_1utils_table_ok.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:14:50 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/06 17:17:39 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_table_pipe_or(t_argtable **arg_table, int *j, int *k, char **cmd)
{
	t_argtable	**temp;
	char		**cmds;

	temp = arg_table;
	cmds = cmd;
	if ((*temp)->cmd && !ft_strcmp(*cmds, "||"))
	{
		initialize_data_table(temp, cmds);
		(*temp)->cmd = ft_strdup("or");
	}
	cmds++;
	*j = 0;
	*k = 0;
	initialize_data_table(temp, cmds);
	return (1);
}

void	set_int_zero(t_table *s)
{
	(*s).i = 0;
	(*s).j = 0;
	(*s).k = 0;
	(*s).arg_table = NULL;
	(*s).temp = NULL;
}

void	free_null(char *str)
{
	free(str);
	str = NULL;
}
