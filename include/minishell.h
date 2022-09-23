/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:37:07 by yjoo              #+#    #+#             */
/*   Updated: 2022/09/23 09:06:03 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

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

char						**g_envp;
typedef struct s_token		t_token;
typedef struct s_cmd		t_cmd;
typedef struct s_cmd_list	t_cmd_list;

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

int		parse(t_cmd_list *cmd_list);
int		is_empty(char *line);
int		get_token_type(char *line, int idx);
int		new_token(t_token **head_token, char *line, int *idx);
t_token	*serach_token(t_token *head, int type);
void	envp_to_word(t_token *head_token);
void	syntax_pipe(t_token *head_token);
void	free_token_list(t_token *head_token);

char	**get_envp(char **envp);
void	signal_setting(void);

void	show_token_list(t_token *head_token);//삭제예정

#endif
