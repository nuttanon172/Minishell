/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:58:24 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/31 17:15:08 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	is_flagn(const char *s)
{
	size_t	i;

	i = 0;
	if (s[i] == '-')
		i++;
	while (s[i])
	{
		if (s[i] == 'n')
			i++;
		else
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	i;

	if (argc == 1)
		return (0);
	i = 1;
	if (!is_flagn(argv[i]))
		i++;
	while (argv[i])
	{
		printf("%s", argv[i++]);
		if (argv[i])
			printf(" ");
	}
	if (is_flagn(argv[1]))
		printf("\n");
	return (0);
}
