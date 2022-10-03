/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:14:23 by siokim            #+#    #+#             */
/*   Updated: 2022/10/03 08:49:13 by siokim           ###   ########.fr       */
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

void	recursive_exec(t_cmd **head, int size, int max)
{
	t_cmd	*node;
	char	*tmp_cmd;
	int		save_stdout;
	int		save_stdin;

	tmp_cmd = 0;
	max = 0;
	node = head[size];
	set_stdfd(&save_stdout, &save_stdin, '0');
	if (ft_redirect(node) == -1)
		return (set_stdfd(&save_stdout, &save_stdin, '1'));
	while (node)
	{
		tmp_cmd = 0;
		if (node->type == WORD)
			tmp_cmd = get_cmds(&node);
		if (node->type >= REDIRIN && node->type <= APPEND)
			node = node->next;
		if (tmp_cmd != 0)
		{
			if (node->next != 0)
				ft_pipe(tmp_cmd);
			else
				ft_cmd(tmp_cmd);
		}
		node = node->next;
	}
	set_stdfd(&save_stdout, &save_stdin, '1');
}

void	ft_exec(t_cmd_list *cmd_list)
{	
	int	size;
	int	i;

	i = -1;
	size = cmd_list->size;
	while (++i < size)
		recursive_exec(cmd_list->head, i, size);
}
