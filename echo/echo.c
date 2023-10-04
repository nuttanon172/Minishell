/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchulkai <vchulkai@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 18:24:04 by naam              #+#    #+#             */
/*   Updated: 2023/09/30 05:45:01 by vchulkai         ###   ########.fr       */
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
	if (ft_strncmp(argv[1], "-n", 2) == 0)
		i++;
	while (argv[i])
	{
		printf("%s", argv[i++]);
		if (argv[i] != NULL)
			printf(" ");
	}
	if (ft_strncmp(argv[1], "-n", 2) != 0)
		printf("\n");
	return (0);
}
