/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 19:37:07 by yjoo              #+#    #+#             */
/*   Updated: 2022/09/12 20:30:49 by yjoo             ###   ########.fr       */
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
	t_cmd	*prev;
	t_cmd	*next;
};

struct s_cmd_list
{
	t_cmd	*head;
	t_cmd	*tail;
	int		size;
};

int		parse(void);
int		is_empty(char *line);

void	signal_setting(void);

#endif
