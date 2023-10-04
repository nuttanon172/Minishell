/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:07:48 by vchulkai          #+#    #+#             */
/*   Updated: 2023/10/04 19:00:51 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE
#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>

int			execve_command(t_argtable **arg_table, char **first_dir);
int			read_default_fd(t_argtable **arg_table);
char		**ft_splitenv(char *first_dir);
size_t		ft_strlen(const char *s);
int			ft_strcmp(char *src, char *dst);
void		print_file_des(int fds, char *s, char c);
int			ft_strncmp(char *src, char *cmp, int n);
char		*ft_strcat(char *src, char *dst);
char		*ft_strndup(char *src, int n);
char		*open_inputdoc(char *filename);
void		write_input_dummy(char *string);
void		here_doc(char *argv);
void		write_to_file_pfd(int fd, int writefile);
void		defualt_input(t_argtable **temp);
void		dup2_and_close(int closed, int new, int old);
int			sub_exec_redirect(t_argtable **temp, int pipeid, char **first_dir);

int	pipex(t_argtable **arg_table, char	**first_dir)
{
	t_argtable	**temp;
	pid_t		pid;
	int			status;

	temp = arg_table;
	if (!ft_strcmp((*temp)->argv[0], "exit") && !(*temp)->next)
		execve((*temp)->cmd, (*temp)->argv, first_dir);
	pid = fork();
	if (!pid)
		exit(execve_command(temp, first_dir));
	else
	{
		waitpid(pid, &status, 0);
		return(WEXITSTATUS(status));
	}
}

int	execve_command(t_argtable **arg_table, char **first_dir)
{
	t_argtable	**temp;
	int			pipeid[2];
	pid_t		pid;
	int			status;
	int			i;

	status = 0;
	i = 0;
	temp = arg_table;
	defualt_input(temp);
	pipe(pipeid);
	pid = fork();
	if (!pid)
	{
		dup2_and_close(pipeid[0], pipeid[1], STDOUT_FILENO);
		close(pipeid[1]);
		execve((*temp)->cmd, (*temp)->argv, first_dir);
		exit(127);
		return (WEXITSTATUS(status));
	}
	waitpid(pid, &status, 0);
	dup2_and_close(pipeid[1], pipeid[0], STDIN_FILENO);
	i = sub_exec_redirect(temp, pipeid[0], first_dir);
	close(pipeid[0]);
	if (WEXITSTATUS(status))
		return (WEXITSTATUS(status));
	return (i);
}

void	defualt_input(t_argtable **temp)
{
	int	fd;

	fd = 0;
	if ((*temp)->infile || (*temp)->heredoc_kw)
	{
		fd = read_default_fd(temp);
		dup2_and_close(fd, fd, STDIN_FILENO);
	}
}

void	dup2_and_close(int closed, int new, int old)
{
	dup2(new, old);
	close(closed);
}

int	sub_exec_redirect(t_argtable **temp, int pipeid, char **first_dir)
{
	int	i;

	i = 0;
	while ((*temp)->redirection[i])
	{
		if (!ft_strncmp((*temp)->redirection[i], "outfile", 7)
			|| !ft_strncmp((*temp)->redirection[i], "append", 6))
		{
			sub_exec_redirect_loop(temp, i, pipeid);
			break ;
		}
		i++;
	}
	if (!(*temp)->outfile && !(*temp)->next)
		print_file_des(pipeid, NULL, 0);
	while ((*temp)->next)
	{
		(*temp) = (*temp)->next;
		return(execve_command(temp, first_dir));
	}
	return (0);
}

void	sub_exec_redirect_loop(t_argtable **temp, int i, int pipeid)
{
	if (!ft_strncmp((*temp)->redirection[i], "outfile", 7)
		|| !ft_strncmp((*temp)->redirection[i], "append", 6))
	{
		if (!ft_strncmp((*temp)->redirection[i], "outfile", 7)
			&& (*temp)->appendfile)
		{
			close(open((*temp)->outfile, O_CREAT | O_WRONLY
					| O_TRUNC, 0777));
			print_file_des(pipeid, (*temp)->appendfile, 'a');
		}
		else if (!ft_strncmp((*temp)->redirection[i], "append", 6)
			&& (*temp)->outfile)
		{
			close(open((*temp)->appendfile, O_CREAT | O_WRONLY
					| O_TRUNC, 0777));
			print_file_des(pipeid, (*temp)->outfile, 'o');
		}
		if (!ft_strncmp((*temp)->redirection[i], "outfile", 7))
			print_file_des(pipeid, (*temp)->outfile, 'o');
		else if (!ft_strncmp((*temp)->redirection[i], "append", 6))
			print_file_des(pipeid, (*temp)->appendfile, 'a');
	}
}

void	print_file_des(int fds, char *s, char c)
{
	int	fd;
	int	writefile;
	int	pid;
	int	status;

	fd = dup(fds);
	if (c == 'o')
		writefile = open(s, O_CREAT | O_WRONLY | O_TRUNC, 777);
	else if (c == 'a')
		writefile = open(s, O_WRONLY | O_APPEND | O_CREAT, 777);
	else if (c == 0)
		writefile = STDOUT_FILENO;
	pid = fork();
	if (!pid)
	{
		write_to_file_pfd(fd, writefile);
		close(fd);
	}
	waitpid(pid, &status, 0);
	close(writefile);
	close(fd);
}

void	write_to_file_pfd(int fd, int writefile)
{
	int		i;
	char	*ans;
	char	str[10];

	i = 0;
	ans = NULL;
	while (1)
	{
		i = read(fd, str, 10);
		ans = ft_strcat(ans, ft_strndup(str, i));
		if (i < 10 || (i == 10 && !str[i - 1]))
			break ;
	}
	write(writefile, ans, ft_strlen(ans));
	free(ans);
	close(writefile);
	close(fd);
	exit(0);
}

int	read_default_fd(t_argtable **arg_table)
{
	int		fd;
	int		i;
	char	*ans;

	i = 0;
	fd = 0;
	ans = NULL;
	while ((*arg_table)->redirection[i])
	{
		if (!ft_strcmp((*arg_table)->redirection[i], "heredoc"))
		{
			here_doc((*arg_table)->heredoc_kw);
			ans = ft_strcat(ans, open_inputdoc(".here_doc"));
		}
		else if (!ft_strcmp((*arg_table)->redirection[i], "infile"))
			ans = ft_strcat(ans, open_inputdoc((*arg_table)->infile));
		i++;
	}
	if (*ans)
	{
		write_input_dummy(ans);
		fd = open(".input_file", O_RDONLY);
	}
	return (fd);
}

char	*open_inputdoc(char *filename)
{
	struct stat	st;
	char		*string;
	int			fd;

	fd = open(filename, O_RDONLY, 777);
	if (fd < 0)
		perror(filename);
	stat(filename, &st);
	string = malloc(sizeof(char) * (st.st_size) + 1);
	string[st.st_size] = '\0';
	read(fd, string, st.st_size);
	close(fd);
	return (string);
}

void	write_input_dummy(char *string)
{
	int	fd;

	fd = open(".input_file", O_CREAT | O_RDWR, 777);
	write(fd, string, ft_strlen(string));
	close(fd);
}