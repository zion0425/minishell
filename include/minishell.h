/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:07:07 by siokim            #+#    #+#             */
/*   Updated: 2022/09/15 15:11:27 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <stdio.h>

void	ft_cmd(char **envp, char *cmd);

/*
typedef struct s_token
{
	int		type;
	char	*token;
	t_token	*prev;
	t_token	*next;
}	t_token;

typedef struct s_cmd
{
	int		type;
	char	*cmd;
	t_cmd	*prev;
	t_cmd	*next;
}	t_cmd;

typedef struct s_cmd_list
{
	t_cmd	*head;
	t_cmd	*tail;
	int		size;
}	t_cmd_list;
*/
#endif
