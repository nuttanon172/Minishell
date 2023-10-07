/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 19:58:24 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/07 17:36:38 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n) && ((s1[i] != '\0') || (s2[i] != '\0')))
	{
		if (s1[i] > s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		if (s1[i] < s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	i;

	if (argc == 1)
		return (0);
	i = 1;
	printf("This is my echo\n");
	if (!ft_strncmp(argv[i], "-n", 2))
		i++;
	while (argv[i])
	{
		printf("%s", argv[i++]);
		if (argv[i] != NULL)
			printf(" ");
	}
	if (ft_strncmp(argv[1], "-n", 2))
		printf("\n");
	return (0);
}
