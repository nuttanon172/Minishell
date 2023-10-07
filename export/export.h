/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:10:33 by ntairatt          #+#    #+#             */
/*   Updated: 2023/10/07 21:40:55 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <stdbool.h>

size_t	ft_strlen(const char *s);
int		ft_counttochar(char *src, char ch);
char	*ft_strdup(char *src);
int		ft_csp(char *src, char ch);
size_t	ft_arglen(char *argv);
char	*ft_strndup(char *src, int n);

#endif