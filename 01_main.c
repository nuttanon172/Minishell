/* ************************************************************************** */
/*                                                                        */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbhuprad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:37:38 by vchulkai          #+#    #+#             */
/*   Updated: 2023/09/26 17:54:36 by lbhuprad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		pi;
	char	first_dir[4096];

	(void)argc;
	(void)argv;
	pi = 0;
	getcwd(first_dir, sizeof(first_dir));
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	write_env(envp, first_dir);
	pi = start_shell(pi, first_dir);
	return (pi);
}

int	start_shell(int pi, char *first_dir)
{
	char		*command;
	t_argtable	*arg_table;
	char		**check;
	char		**temp_env;
	t_argtable	*temp_table;

	while (1)
	{
		check = NULL;
		arg_table = NULL;
		temp_env = ft_splitenv(first_dir);
		command = get_from_readline(temp_env);
		if (*command)
			add_history(command);
		command = ft_add_ifsp_nosp(command);
		check = ft_split_c(command, ' ');
		replace_variable(check, temp_env, pi);
		if (!check_heredoc(check) && check[0])
		{
			arg_table = create_table(&check, temp_env);
			temp_table = arg_table;
			if (!ft_strcmp(arg_table->cmd, "cd") && arg_table->next)
				temp_table = arg_table->next;
			else if (!ft_strcmp(temp_table->cmd, "cd") && !temp_table->next)
				chang_directory(temp_table->argv[1]);
			else if (check_char_sptable(temp_table))
				pi = pipex(&temp_table, temp_env);
			free_all_table(arg_table);
		}
		free(command);
		free_chardstar(check);
		free_chardstar(temp_env);
		wait(NULL);	
		if (!access(".here_doc", F_OK))
			unlink(".here_doc");
		if (!access(".input_file", F_OK))
			unlink(".input_file");
	}
	
}

void chang_directory(char *path)
{
	struct stat s;

	if(stat(path, &s) == 0)
		chdir(path);
}

int	check_char_sptable(t_argtable *arg_table)
{
	int	i;

	i = 0;
	while (arg_table->redirection[i])
	{
		if (!ft_strcmp(arg_table->redirection[i], "infile") 
			&& check_spcharactor(arg_table->infile))
				return (0);
		else if (!ft_strcmp(arg_table->redirection[i], "outfile")
			&& check_spcharactor(arg_table->outfile))
				return (0);
		else if (!ft_strcmp(arg_table->redirection[i], "append")
			&& check_spcharactor(arg_table->appendfile))
				return (0);
		else if (!ft_strcmp(arg_table->redirection[i], "heredoc") 
			&& check_spcharactor(arg_table->heredoc_kw))
			return (0);
		i++;
	}
	return (1);
}

int	check_spcharactor(char *str)
{
	if (!str || str[0] == '>' || str[0] == '<' || str[0] == '|' || str[0] == ';' 
		|| str[0] == '&' || str[0] == '#' || str[0] == '-' || str[0] == '(' 
			|| str[0] == ')')
	{
		write (2, "Syntax error near unexpected token: '", 37);
		if(str)
			write (2, str, ft_strlen(str));
		write (2, "'\n", 2);
		return(1);
	}
	return(0);
}

int	check_heredoc(char **cmd)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (cmd[i])
	{
		if (!ft_strcmp(cmd[i], "<<"))
		{
			if (!cmd[i + 1] || !ft_strcmp(cmd[i + 1], "|")
				|| !ft_strcmp(cmd[i + 1], "<")
				|| !ft_strcmp(cmd[i + 1], ">") || !ft_strcmp(cmd[i + 1], ">>"))
			{
				write (2, "Syntax error near unexpected token: ''\n", 39);
				status = 1;
			}
		}
		i++;
	}
	return (status);
}

void	here_doc(char *argv)
{
	char	*buffer;
	int		f;
	ssize_t	bytes_read;

	f = openfile(".here_doc", 'O');
	buffer = (char *)malloc(sizeof(char) * (ft_strlen(argv) + 1));
	if (!buffer)
		return ;
	while (write(1, "heredoc> ", 9))
	{
		while (1)
		{
			bytes_read = read(STDIN_FILENO, buffer, ft_strlen(argv) + 1);
			if (buffer[bytes_read - 1] == '\n'
				&& !ft_strncmp(buffer, argv, ft_strlen(argv)))
			{
				close(f);
				free(buffer);
				return ;
			}
			else if (write(f, buffer, bytes_read)
				&& buffer[bytes_read - 1] == '\n' && buffer)
				break ;
		}
	}
}

int	openfile(char *fname, char mode)
{
	int	fd;

	if (mode == 'I' && access(fname, R_OK))
	{
		perror(fname);
		exit(1);
	}
	else if (mode == 'I' )
		return (open(fname, O_RDONLY, O_NONBLOCK | O_SYNC | O_EXCL));
	else
	{
		fd = open(fname, O_CREAT | O_WRONLY | O_TRUNC,
				0000400 | 0000200 | 0000040 | 0000020 | 0000004 | O_NONBLOCK);
		if (fd < 0)
			return (perror(fname), -1);
	}
	return (fd);
}

char	*get_path(char *argv, char **first_dir)
{
	char	**path;
	char	*temp;
	int		i;
	char	*stjoin;

	i = 0;
	if (!ft_strcmp(argv, "cd"))
		return (argv);
	temp = ft_getenv(first_dir, ft_strndup("PATH", 4));
	path = ft_split_c(temp, ':');
	free(temp);
	while (path[i++])
	{
		stjoin = ft_strcat(ft_strcat(ft_strndup(path[i - 1],
						ft_strlen(path[i - 1])), ft_strndup("/", 1)),
				ft_strndup(argv, ft_strlen(argv)));
		if (!access(stjoin, X_OK))
			free_chardstar(path);
		if (!access(stjoin, X_OK))
			return (free(argv), stjoin);
		free(stjoin);
		stjoin = NULL;
	}
	free_chardstar(path);
	if (ft_strcmp(argv, "cd"))
	{
		write(2, argv, ft_strlen(argv));
		write(2, ": Command not found\n", 20);
	}
	return (argv);
}

void	free_chardstar(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		path[i++] = NULL;
	}
	free(path);
	path = NULL;
}

void	free_re_arg(t_argtable **temp)
{
	free_chardstar((*temp)->redirection);
	free_chardstar((*temp)->argv);
}

char	*get_command(char *str)
{
	size_t		i;
	size_t		n;
	char		*ans;

	ans = NULL;
	n = ft_strlen(str) - 1;
	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] == '/')
			break ;
		i--;
	}
	if (i >= 0)
		ans = ft_strndup(str + i, n - i);
	else
		ans = ft_strdup(str);
	free(str);
	return (ans);
}

char	*return_lebel(char *c)
{
	if (!ft_strcmp(c, ">"))
		return (ft_strdup("outfile"));
	if (!ft_strcmp(c, ">>"))
		return (ft_strdup("append"));
	if (!ft_strcmp(c, "<"))
		return (ft_strdup("infile"));
	if (!ft_strcmp(c, "<<"))
		return (ft_strdup("heredoc"));
	return (NULL);
}

void	initialize_data_table(t_argtable **temp, char **cmd)
{
	int	i;

	if ((*temp))
	{
		(*temp)->next = (t_argtable *)malloc(sizeof(t_argtable));
		(*temp) = (*temp)->next;
	}
	else if (!(*temp))
	{
		(*temp) = (t_argtable *)malloc(sizeof(t_argtable));
		(*temp)->next = NULL;
	}
	i = count_command_arg(cmd);
	(*temp)->argv = (char **)malloc(sizeof(char *) * (i + 1));
	(*temp)->argv[i] = NULL;
	i = count_redirection(cmd);
	(*temp)->redirection = (char **)malloc(sizeof(char *) * (i + 1));
	(*temp)->redirection[i] = NULL;
	(*temp)->next = NULL;
	(*temp)->cmd = NULL;
	(*temp)->heredoc_kw = NULL;
	(*temp)->infile = NULL;
	(*temp)->outfile = NULL;
	(*temp)->appendfile = NULL;
}

int	count_command_arg(char **cmd)
{
	char	**temp;
	int		i;

	if (!cmd || !*cmd)
		return(0);
	temp = cmd;
	i = 0;
	while (*temp && ft_strcmp(*temp, "|") && ft_strcmp(*temp, "||"))
	{
		if (!ft_strcmp(*temp, "<") || !ft_strcmp(*temp, "<<") 
			|| !ft_strcmp(*temp, ">") || !ft_strcmp(*temp, ">>"))
			*temp++;
		else
			i++;
		if (*temp)
			*temp++;
	}
	return (i);
}

int	count_redirection(char **cmd)
{
	char	**temp;
	int		i;

	if (!cmd || !*cmd)
		return(0);
	temp = cmd;
	i = 0;
	while (*temp && ft_strcmp(*temp, "|") && ft_strcmp(*temp, "||"))
	{
		if (!ft_strcmp(*temp, "<") || !ft_strcmp(*temp, "<<") 
			|| !ft_strcmp(*temp, ">") || !ft_strcmp(*temp, ">>"))
			i++;
		*temp++;
	}
	return (i);
}

void	replace_variable(char **cmd, char **env, int pi)
{
	bool	is_insq;
	bool	is_indq;
	int		*i;

	is_indq = false;
	is_insq = false;
	i = malloc(sizeof(int) * 2);
	i[0] = 0;
	i[1] = 0;
	while (cmd[i[0]])
	{
		if (cmd[i[0]][i[1]] == '\"')
			is_indq = !is_indq;
		if (!is_indq && cmd[i[0]][i[1]] == '\'')
			is_insq = !is_insq;
		if (!is_insq && cmd[i[0]][i[1]] == '$')
			sub_replace_veriable(cmd, &i, pi, env);
		if (cmd[i[0]][i[1]])
			i[1]++;
		else
		{
			i[0]++;
			i[1] = 0;
		}
	}
	free(i);
	// free_chardstar(env);
}

void	sub_replace_veriable(char **cmd, int **i, int pi, char **env)
{
	int	k;

	(*i)[1]++;
	k = 0;
	while (cmd[(*i)[0]][(*i)[1]] && cmd[(*i)[0]][(*i)[1]] != '\'' && cmd[(*i)[0]][(*i)[1]] != '\"'
			&& cmd[(*i)[0]][(*i)[1]] && cmd[(*i)[0]][(*i)[1]] != '$' && cmd[(*i)[0]][(*i)[1]] != ' '
			&& cmd[(*i)[0]][(*i)[1]] != '?')
	{
		k++;
		(*i)[1]++;
	}
	if (cmd[(*i)[0]][(*i)[1]] != '?')
		cmd[(*i)[0]] = ft_strcat(
			ft_strcat(ft_strndup(cmd[(*i)[0]], (*i)[1] - k - 1), ft_getenv(env, ft_strndup(cmd[(*i)[0]] + (*i)[1] - k, k))),
				ft_strndup(cmd[(*i)[0]] + (*i)[1], ft_strlen(cmd[(*i)[0]] + (*i)[1])));
	else
		cmd[(*i)[0]] = ft_strcat(ft_strcat(ft_strndup(cmd[(*i)[0]], (*i)[1] - 1),
					ft_strdup(ft_itoa(pi))), ft_strndup(cmd[(*i)[0]] + (*i)[1] + 1,
					ft_strlen(cmd[(*i)[0]] + (*i)[1] + 1)));
}

char	*ft_itoa(int nbr)
{
	long long		n;
	int				len;
	char			*result;

	n = nbr;
	len = 0;
	if (n == 0)
		len = 1;
	while (n)
	{
		n /= 10;
		len++;
	}
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	n = nbr;
	if (n == 0)
		result[0] = '0';
	while (n)
	{
		result[--len] = ((n % 10) + '0');
		n /= 10;
	}
	return (result);
}

int	ft_counttochar(char *src, char ch)
{
	char	*temp;
	int		i;
	bool	is_insq;
	bool	is_indq;

	is_insq = false;
	is_indq = false;
	i = 0;
	temp = src;
	if (*temp == ch)
		return (0);
	while (*temp && (*temp != ch || is_indq || is_insq))
	{
		if (!is_insq && *temp == '\"')
			is_indq = !is_indq;
		else if (!is_indq && *temp == '\'')
			is_insq = !is_insq;
		i++;
		temp++;
	}
	if (!*temp)
		return (-1);
	else
		return (i);
}

char	*ft_add_ifsp_nosp(char *cmd)
{
	int		i;
	int		j;
	char	*ans;
	bool	is_indq;
	bool	is_insq;

	is_indq = false;
	is_insq = false;
	i = count_special_character(cmd) * 2;
	ans = malloc(sizeof(char) * (ft_strlen(cmd) + i + 1));
	i = 0;
	j = 0;
	while (cmd[i] == ' ')
		i++;
	while (cmd[i])
	{
		is_in_q(cmd[i], &is_indq, &is_insq);
		if (!is_indq && !is_insq && (cmd[i] == '|' || cmd[i] == '<'
				|| cmd[i] == '>' || cmd[i] == '&') && cmd[i + 1])
			add_space(&j, &i, &ans, &cmd);
		else
			ans[j++] = cmd[i++];
	}
	ans[j] = '\0';
	return (free(cmd), ans);
}

void	ft_charsetzero(char **chars, int n)
{
	while (n >= 0)
	{
		(*chars)[n] = '\0';
		n--;
	}
}

void	add_space(int *j, int *i, char **ans, char **cmd)
{
	int	t;

	t = 0;
	if (*j != 0)
		(*ans)[(*j)++] = ' ';
	while (((*cmd)[*i] == '|' || (*cmd)[*i] == '<' || (*cmd)[*i] == '>'))
	{
		t++;
		(*ans)[(*j)++] = (*cmd)[(*i)++];
		if ((*cmd)[*i] != (*cmd)[*i - 1] || t == 2)
			break ;
	}
	(*ans)[(*j)++] = ' ';
}

void	is_in_q(char c, bool *is_indq, bool *is_insq)
{
	if (c == '\"')
		*is_indq = !(*is_indq);
	if (!is_indq && c == '\'')
		*is_insq = !(*is_insq);
}

int	count_special_character(char *command)
{
	int		i;
	bool	is_indq;
	bool	is_insq;
	char	*t;

	i = 0;
	t = command;
	is_indq = false;
	is_insq = false;
	while (*t)
	{
		if (*t == '\"')
			is_indq = !is_indq;
		if (!is_indq && *t == '\'')
			is_insq = !is_insq;
		if (!is_indq && !is_insq && (*t == '|' || *t == '<' || *t == '>'))
		{
			while ((*t == '>' && *(t + 1) == '>')
				|| (*t == '<' && *(t + 1) == '<'))
				t++;
			i++;
		}
		t++;
	}
	return (i);
}

void	clear_q(char **cmd)
{
	bool	is_indq;
	bool	is_insq;
	int		i;
	int		j;

	is_indq = false;
	is_insq = false;
	i = 0;
	j = 0;
	while (cmd[i])
	{
		cmd[i] = replace_q(cmd[i]);
		i++;
	}
}

char	*replace_q(char *cmd)
{
	char	*ans;
	bool	is_indq;
	bool	is_insq;
	int		i;
	int		j;

	i = 0;
	j = 0;
	is_indq = false;
	is_insq = false;
	ans = NULL;
	ans = malloc(sizeof(char) * (ft_strlen(cmd) - count_qoute(cmd) + 1));
	while (cmd[i])
	{
		if (!is_insq && cmd[i] == '\"')
			is_indq = !is_indq;
		else if (!is_indq && cmd[i] == '\'')
			is_insq = !is_insq;
		else
			ans[j++] = cmd[i];
		i++;
	}
	ans[j] = '\0';
	free(cmd);
	return (ans);
}

int	count_qoute(char *cmd)
{
	bool	is_indq;
	bool	is_insq;
	char	*temp;
	int		i;

	is_indq = false;
	is_insq = false;
	temp = cmd;
	i = 0;
	while (*temp)
	{
		if ((!is_insq && *temp == '\"') || (is_indq && *temp == '\''))
		{
			if (!is_insq && *temp == '\"')
				is_indq = !is_indq;
			if (!is_indq && *temp == '\'')
				is_insq = !is_insq;
			i++;
		}
		else if ((!is_indq && !is_insq) && (*temp == '\'' || *temp == '\"'))
			i++;
		temp++;
	}
	return(i);
}