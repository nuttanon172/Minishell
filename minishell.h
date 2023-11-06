/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntairatt <ntairatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 16:37:53 by vchulkai          #+#    #+#             */
/*   Updated: 2023/11/06 15:44:47 by ntairatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <dirent.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>
# include <termios.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/ioctl.h>

# define HISTORY_FILE "/.isworld_history"
# define PROMPT ":\033[0;34mIs\033[0;33mWorld\033[0;32m<$>\033[0m "

int	g_pi;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}	t_env;

typedef struct s_key_heredoc
{
	char					*kw;
	struct s_key_heredoc	*next;
}	t_keyword;

typedef struct s_argtable
{
	char				*cmd;
	char				**argv;
	char				**redirection;
	char				*outfile;
	char				*infile;
	char				*appendfile;
	t_keyword			*heredoc_kw;
	struct s_argtable	*next;
}	t_argtable;

typedef struct s_table
{
	t_argtable			*arg_table;
	t_argtable			*temp;
	char				**cmd;
	int					i;
	int					j;
	int					k;
}	t_table;

char		*get_from_readline(void);
size_t		ft_strlen(const char *s);
char		**ft_split_c(char *string, char ch);
int			ft_csp(char *src, char ch);
int			ft_counttochar(char *src, char ch);
char		*ft_strndup(char *src, int n);
char		**ft_splitenv(char *first_dir);
int			count_special_character(char *command);
char		*ft_add_ifsp_nosp(char *cmd);
char		*ft_getenv(char **env, char	*var);
int			ft_strncmp(char *src, char *cmp, size_t n);
void		replace_variable(char **cmd, char **env, int pi);
char		*ft_strcat(char *src, char *dst);
char		*replace_q(char *cmd);
void		clear_q(char **cmd);
t_argtable	*create_table(char ***cmd, char **first_dir);
void		free_all_table(t_argtable *arg_table);
void		free_chardstar(char **path);
char		*get_path(char *argv, char **first_dir);
int			ft_strcmp(char *src, char *dst);
char		*here_doc(char *argv);
void		initialize_data_table(t_argtable **temp, char **cmd);
char		*ft_strdup(char *src);
char		*return_lebel(char *c);
int			pipex(t_argtable **arg_table, char	***first_dir);
int			check_heredoc(char **cmd);
char		*ft_itoa(int nbr);
void		create_table_redirect(t_argtable **arg_table, \
				char **cmd, int *i, int *k);
void		free_re_arg(t_argtable **temp);
int			create_table_pipe_or(t_argtable **arg_table, int *j, \
				int *k, char **cmd);
int			start_shell(char **temp_env);
void		add_space(int *j, int *i, char **ans, char **cmd);
void		is_in_q(char c, bool *is_indq, bool *is_insq);
void		sig_handler(int sig_number);
char		*ft_strcat(char *src, char *dst);
char		**check_quote(int *signal, char **line, size_t *i, char what_quote);
void		sub_replace_veriable(char **cmd, int **i, int pi, char **env);
void		check_pipe_and_return_line(char **line);
void		set_int_zero(t_table *s);
void		free_null(char *str);
void		sub_exec_redirect_loop(t_argtable **temp, int i, int pipeid);
int			write_input_dummy(char *string);
int			count_command_arg(char **cmd);
int			count_redirection(char **cmd);
int			check_char_sptable(t_argtable *arg_table);
int			check_spcharactor(char *str);
void		chang_directory(char *path, char **env);
int			count_newline(char *src);
int			count_to_newline(char *src);
void		set_zero_dchar(char **ans, int k);
void		*ft_strndup_env(char **dst, char *src, int n);
char		*readline(const char *prompt);
void		add_history(char *string);
int			rl_on_new_line(void);
void		rl_redisplay(void);
void		rl_replace_line(const char *text, int clear_undo);
int			execve_command(t_argtable **arg_table, char **first_dir);
int			read_default_fd(t_argtable **arg_table, int pipeid);
void		print_file_des(int fds, char *s, char c);
char		*open_inputdoc(char *filename, int pipeid);
void		write_to_file_pfd(int fd, int writefile);
void		defualt_input(t_argtable **temp, int pipeid);
void		dup2_and_close(int closed, int new, int old);
int			sub_exec_redirect(t_argtable **temp, int pipeid, char **first_dir);
void		get_path_util(char *argv, char **path);
void		check_inq(char ch, bool *is_indq, bool *is_insq);
void		free_s(char *command, char **check);
void		find_home_old(char **previous, char **home, char **temp);
void		my_env(char **envp, char *first_dir);
int			ft_atoi(char *nbr);
void		add_path(char **env, char *first_dir);
char		**ft_strddup(char **envp);
int			check_in_env(char **envp, char *check);
void		change_level(char **temp_env);
void		ft_unset(char **envp, char **argv);
size_t		ft_arglen(char *argv);
void		ft_export(char ***envp, char **argv);
int			check_builtin(t_argtable **temp, char ***envp);
void		isdir(const char *fileName);
int			check_ex_unset(char *argv, char *cmd);
void		printerror(char *cmd, char *command);
int			child_process(t_argtable **temp, int pipeid[2], char ***first_dir);
void		sub_util(void);
int			count_heredoc(char **cmd);
int			check_char_sptable_util(t_argtable *arg_table, int i);

#endif
