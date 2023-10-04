/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_utils_env_split_ok.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vchulkai <vchulkai@42student.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 18:28:52 by lbhuprad          #+#    #+#             */
/*   Updated: 2023/09/30 01:03:47 by vchulkai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_env(char **envp, char *first_dir)
{
	int			fd;
	struct stat	st;
	char		*file_path;
	
	file_path = ft_strcat(ft_strdup(first_dir), ft_strdup("/.minishell.env"));
	fd = open(file_path, O_WRONLY | O_CREAT, 0777);
	stat(file_path, &st);
	if (!st.st_size)
	{
		while (*envp)
		{
			if (ft_strncmp(*envp, "PATH=", 5))
				write(fd, *envp, ft_strlen(*envp));
			else
			{
				write(fd, *envp, 5);
				write(fd, first_dir, ft_strlen(first_dir));
				write(fd, "/bin/:", 6);
				write(fd, *envp + 5, ft_strlen(*envp + 5));
			}
			write(fd, "\n", 1);
			envp++;
		}
	}
	close(fd);
	free(file_path);
}

char	**ft_splitenv(char *first_dir)
{
	int			fd[2];
	char		**envp;
	char		*ans;
	char		*file_dirs;
	char		str[10];

	ans = NULL;
	envp = NULL;
	file_dirs = ft_strcat(ft_strdup(first_dir), ft_strdup("/.minishell.env"));
	fd[0] = open(file_dirs, O_RDONLY, 0777);
	while (1)
	{
		fd[1]  = read(fd[0], str, 10);
		if (fd[1] <= 0)
			break ;
		ans = ft_strcat(ans, ft_strndup(str, fd[1]));
	}
	envp = ft_split_to_env(ans, '\n');
	free(ans);
	ans = NULL;
	free(file_dirs);
	file_dirs = NULL;
	close(fd[0]);
	return (envp);
}

char	**ft_split_to_env(char *string, char ch)
{
	char	**ans;
	char	*temp;
	int		i;
	int		j;
	int		k;
	
	i = 0;
	j = 0;
	temp = string;
	k = count_newline(temp);
	ans = (char **)malloc(sizeof(char *) * (k + 1));
	while (*temp)
	{
		ans[j++] = ft_strndup(temp, count_to_newline(temp));
		while (*temp)
		{
			if (*temp != ch)
				temp++;
			else
			{
				temp++;
				break;
			}
		}
	}
	temp = NULL;
	ans[k] = NULL;
	return (ans);
}

int	count_to_newline(char *src)
{
	char	*temp;
	int		i;

	i = 0;
	temp = src;
	while(*temp)
	{
		if(*temp == '\n' || !*temp)
		{
			if (!*temp)
				i--;
			break;
		}
		i++;
		temp++;
	}
	return (i);
}

int	count_newline(char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(src[i])
	{
		if (src[i] == '\n')
			j++;
		i++;
	}
	return (j);
}


char	**ft_split_c(char *string, char ch)
{
	char	**ans;
	char	*temp;
	int		i;

	i = 0;
	temp = string;
	if (temp == NULL)
		return (NULL);
	while (*temp == ' ')
		temp++;
	ans = malloc(sizeof(char *) * (ft_csp(temp, ch) + 2));
	while (i <= ft_csp(string, ch))
	{
		if (ft_counttochar(temp, ch) != -1)
		{
			ans[i++] = ft_strndup(temp, ft_counttochar(temp, ch));
			temp = temp + ft_counttochar(temp, ch) + 1;
			while (*temp == ch)
				temp++;
		}
		else
			ans[i++] = ft_strndup(temp, ft_strlen(temp));
	}
	ans[i] = NULL;
	return (ans);
}


int	ft_csp(char *src, char ch)
{
	int		i;
	bool	is_insq;
	bool	is_indq;
	char	*temp;

	is_insq = false;
	is_indq = false;
	i = 0;
	temp = src;
	while (*temp)
	{
		if (!is_insq && *temp == '\"')
			is_indq = !is_indq;
		else if (!is_indq && *temp == '\'')
			is_insq = !is_insq;
		if (*temp == ch && *(temp + 1) != ch && !is_indq && !is_insq)
			i++;
		temp++;
	}
	return (i);
}

char	*ft_getenv(char **env, char	*var)
{
	int		i;
	char	*ans;
	char	*temp;

	i = 0;
	// ans = NULL;
	while (env[i])
	{
		temp = env[i];
		if (!ft_strncmp(temp, var, ft_strlen(var)))
		{
			temp = temp + ft_strlen(var) + 1;
			ans = ft_strdup(temp);
		}
		i++;
	}
	free(var);
	// free_chardstar(env);
	return (ans);
}
