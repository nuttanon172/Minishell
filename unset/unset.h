/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 22:47:19 by naam              #+#    #+#             */
/*   Updated: 2023/09/25 18:55:00 by naam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UNSET_H
# define UNSET_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "../minishell.h"

size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_counttochar(char *src, char ch);
char	*ft_strdup(char *src);
int		t_csp(char *src, char ch);
char	**ft_split_c(char *string, char ch);
char	**ft_splitenv(void);

#endif
