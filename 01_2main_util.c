/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_2main_util.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:53:51 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/06 18:54:12 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_inq(char ch, bool *is_indq, bool *is_insq)
{
	if (ch == '\"')
		*is_indq = !(*is_indq);
	if (!is_indq && ch == '\'')
		*is_insq = !(*is_insq);
}
