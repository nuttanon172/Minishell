/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbhuprad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 14:42:38 by naam              #+#    #+#             */
/*   Updated: 2023/09/26 14:47:53 by lbhuprad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>

int	ft_atoi(const char *str)
{
	int			i;
	int			r;
	int			ans;

	i = 0;
	r = 1;
	ans = 0;
	while ((str[i] == '\n' || str[i] == '\r' || str[i] == ' '
			|| str[i] == '\t' || str[i] == '\v' || str[i] == '\f') && str[i])
		i++;
	if (str[i] == '-')
		r = -1;
	while (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (ans < 0 && r == -1)
			return (0);
		if (ans < 0 && r == 1)
			return (-1);
		ans = 10 * ans + str[i] - '0';
		i++;
	}
	return (r * ans);
}

int	main(int argc, char **argv)
{
	int	exit_code;

	if (argc == 1)
		exit_code = errno;
	else
		exit_code = ft_atoi(argv[1]);
	return (exit(exit_code), exit_code);
}
