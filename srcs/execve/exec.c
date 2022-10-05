/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:14:23 by siokim            #+#    #+#             */
/*   Updated: 2022/10/06 03:48:37 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_stdfd(int *save_stdout, int *save_stdin, char isset)
{
	if (isset == '0')
	{
		*save_stdout = dup(1);
		*save_stdin = dup(0);
	}
	else
	{
		dup2(*save_stdout, 1);
		dup2(*save_stdout, 0);
	}
}

void	file_error(int *stdout, int *stdin, char *msg)
{
	set_stdfd(stdout, stdin, '1');
	printf("%s : No such file or directory\n", msg);
}

void	recursive_exec(t_cmd **head, int size, int max)
{
	t_cmd	*node;
	char	*tmp_cmd;
	int		s_stdout;
	int		s_stdin;

	node = head[size];
	set_stdfd(&s_stdout, &s_stdin, '0');
	if (ft_redirect(node) == -1)
		return (set_stdfd(&s_stdout, &s_stdin, '1'));
	while (node)
	{
		tmp_cmd = 0;
		if (node->type == BUILTIN)
		{
			ft_bulitin(&node, max);
			continue ;
		}
		if (node->type == WORD)
			tmp_cmd = get_cmds(&node);
		if (node->type >= REDIRIN && node->type <= APPEND)
		{
			node = node->next;
			if (tmp_cmd != 0 && node->next->type == WORD)
				return (file_error(&s_stdout, &s_stdin, node->next->cmd));
		}
		if (tmp_cmd != 0)
			ft_cmd(tmp_cmd);
		node = node->next;
	}
	set_stdfd(&s_stdout, &s_stdin, '1');
}

void	ft_exec(t_cmd_list *cmd_list)
{	
	int	size;

	size = cmd_list->size;
	if (size == 1)
	{
		if (!ft_strncmp(cmd_list->head[0]->cmd, "", 1))
			return ;
		--size;
		recursive_exec(cmd_list->head, size, size);
	}
	else if (size > 1)
		ft_pipe(cmd_list->head, 0, --size);
}
