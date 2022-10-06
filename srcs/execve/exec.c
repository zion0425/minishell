/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:14:23 by siokim            #+#    #+#             */
/*   Updated: 2022/10/06 13:06:38 by siokim           ###   ########.fr       */
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

void	execmd(char *tmp_cmd)
{
	if (tmp_cmd != 0)
		ft_cmd(tmp_cmd);
}

void	recursive_exec(t_cmd **h, int s, int max)
{
	char	*tmp_cmd;
	int		s_io[2];

	set_stdfd(&s_io[0], &s_io[1], '0');
	if (ft_redirect(h[s], max) == -1)
		return (set_stdfd(&s_io[0], &s_io[1], '1'));
	while (h[s])
	{
		tmp_cmd = 0;
		if (h[s]->type == BUILTIN)
		{
			ft_bulitin(&h[s], max);
			continue ;
		}
		if (h[s]->type == WORD)
			tmp_cmd = get_cmds(&h[s]);
		if (h[s]->type >= REDIRIN && h[s]->type <= APPEND)
			h[s] = h[s]->next;
		if (h[s]->type >= REDIRIN && h[s]->type <= APPEND)
			if (tmp_cmd != 0 && h[s]->next->type == WORD)
				return (file_error(&s_io[0], &s_io[1], h[s]->next->cmd));
		execmd(tmp_cmd);
		h[s] = h[s]->next;
	}
	set_stdfd(&s_io[0], &s_io[1], '1');
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
	else if (--size >= 1)
		ft_pipe(cmd_list->head, 0, size);
}
