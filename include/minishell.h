/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:37:07 by yjoo              #+#    #+#             */
/*   Updated: 2022/09/22 16:13:21 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
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
	t_cmd	*left;
	t_cmd	*right;
};

struct s_cmd_list
{
	t_cmd	*head;
	t_cmd	*tail;
	int		size;
};

int		parse(void);
int		is_empty(char *line);
int		get_token_type(char *line, int idx);
int		new_token(t_token **head_token, char *line, int *idx);
void	free_token_list(t_token *head_token);

void	signal_setting(void);

void	show_token_list(t_token *head_token);//삭제예정

#endif
