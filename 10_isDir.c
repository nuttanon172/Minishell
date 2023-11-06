/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_isDir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:32:45 by vchulkai          #+#    #+#             */
/*   Updated: 2023/11/06 16:46:09 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	isdir(const char *fileName)
{
	struct stat	path;

	stat(fileName, &path);
	if (S_ISREG(path.st_mode) == 0 && !access(fileName, X_OK))
	{
		write(2, fileName, ft_strlen(fileName));
		write(2, ": is a directory\n", 18);
		exit(126);
	}
}
