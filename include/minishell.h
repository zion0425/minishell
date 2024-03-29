/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:37:07 by yjoo              #+#    #+#             */
/*   Updated: 2022/10/06 13:40:44 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <string.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>

# define INFILE		0
# define OUTFILE	1
# define WORD		0
# define REDIRIN	1
# define REDIROUT	2
# define HEREDOC	3
# define APPEND		4
# define PIPE		5
# define QUOTE		6
# define DQUOTE		7
# define DOLLAR		8
# define BUILTIN	9

typedef struct s_token		t_token;
typedef struct s_cmd		t_cmd;
typedef struct s_cmd_list	t_cmd_list;
typedef struct s_gloval		t_gloval;
t_gloval					g_var;

struct s_gloval
{
	char	**envp;
	int		exit_code;
};

struct s_token
{
	int		type;
	char	*token;
	t_token	*prev;
	t_token	*next;
};

struct s_cmd
{
	int		type;
	char	*cmd;
	t_cmd	*next;
	t_cmd	*prev;
};

struct s_cmd_list
{
	t_cmd	**head;
	int		size;
};
void	ft_pipe(t_cmd **head, int start, int size);
int		print_error(char *err_msg);
void	ft_exec(t_cmd_list *cmds);
int		openfile(char *filename, char format);
int		ft_redirect(t_cmd *node, int size);
void	ft_pipecmd(char *cmd);
void	ft_cmd(char *cmd);
char	*get_cmds(t_cmd **node);
void	recursive_exec(t_cmd **h, int s, int max);
void	set_stdfd(int *save_stdout, int *save_stdin, char isset);
void	ft_simplecmd(char *cmd);
void	ft_bulitin(t_cmd **node, int size);
int		parse(t_cmd_list *cmd_list);
int		is_empty(char *line);
int		get_token_type(char *line, int idx);
int		new_token(t_token **head_token, char *line, int *idx);
int		envp_convert(t_token *head, int cnt);
char	*dollar_token_handle(char *line, int *idx, t_token *token);
void	free_token_list(t_token *head_token, char *line);
void	input_token(t_token *new_token, char *line, int *idx);
void	merge_token(char *line, int *idx, t_token *new_token);
char	*find_value(char *key, char *ret, int idx, int jdx);
int		new_cmd_list(t_cmd **head_cmd, t_token *head_token);
t_token	*search_token(t_token *head, int type);
void	free_split(char **split);
char	**get_envp(char **envp);
int		is_whitespace(char c);
void	signal_setting(int option);
void	echoctl(int option);
void	env(void);
void	echo(t_cmd **cur);
void	pwd(void);
void	cd(t_cmd **node, int size);
void	unset(t_cmd *cmd);
void	ft_exit(t_cmd **node, int size);
void	export(t_cmd **node);
void	tmp_unset(char *str);
void	show_token_list(t_token *head_token);
void	show_cmd(t_cmd **head_cmd);
char	**new_envp(char *str, int size);
char	*get_pwd(void);
int		heredoc(t_cmd *node);

#endif
