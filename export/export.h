/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:27:37 by naam              #+#    #+#             */
/*   Updated: 2023/10/06 19:56:50 by ntairatt         ###   ########.fr       */
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
char	**ft_split_c(char *string, char ch);

#endif