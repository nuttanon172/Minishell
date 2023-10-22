/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:14:52 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/22 22:28:50 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	int	i;

	i = 0;
	(void)argc;
	(void)argv;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
