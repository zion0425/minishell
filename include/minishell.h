/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:37:07 by yjoo              #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/09/22 16:13:21 by siokim           ###   ########.fr       */
=======
/*   Updated: 2022/10/01 20:10:03 by yjoo             ###   ########.fr       */
>>>>>>> yjoo
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
<<<<<<< HEAD
# include <stdio.h>
=======
# include <termios.h>
>>>>>>> yjoo
# include <signal.h>
# include <sys/stat.h>
# include <errno.h>
# include <fcntl.h>
# include <string.h>

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

void	print_error(char *err_msg);
void	ft_cmd(char **envp, char *cmd);
int		openfile(char *filename, char format);

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

struct s_gloval
{
	char	**envp;
	int		exit_code;
};


int		parse(t_cmd_list *cmd_list);
int		is_empty(char *line);
int		get_token_type(char *line, int idx);
int		new_token(t_token **head_token, char *line, int *idx);
int		envp_convert(t_token *head, int cnt);
char	*dollar_token_handle(char *line, int *idx, t_token *token);
void	free_token_list(t_token *head_token, char *line);

int		new_cmd_list(t_cmd **head_cmd, t_token *head_token);
t_token	*search_token(t_token *head, int type);

void	free_split(char **split);

char	**get_envp(char **envp);
int		is_whitespace(char c);
void	signal_setting(void);

void	show_token_list(t_token *head_token);//삭제예정
void	show_cmd(t_cmd **head_cmd);

#endif
