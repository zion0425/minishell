/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 14:15:39 by yjoo              #+#    #+#             */
/*   Updated: 2022/10/03 04:39:28 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	free_cmd_list(t_cmd_list *cmd_list)
{
	int		idx;
	t_cmd	*cur_cmd;

	idx = 0;
	if (!cmd_list->head)
		return ;
	while (idx < cmd_list->size)
	{
		cur_cmd = cmd_list->head[idx];
		while (cur_cmd)
		{
			free(cur_cmd->cmd);
			cmd_list->head[idx] = cmd_list->head[idx]->next;
			free(cur_cmd);
			cur_cmd = cmd_list->head[idx];
		}
		free(cmd_list->head[idx]);
		idx++;
	}
	free(cmd_list->head);
	ft_bzero(cmd_list, sizeof(t_cmd_list));
}

void	echoctl(int option)
{
	struct termios	attr;

	tcgetattr(STDIN_FILENO, &attr);
	if (option == 0)
		attr.c_lflag &= ~ECHOCTL;
	else
		attr.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &attr);
}

int	main(int argc, char **argv, char **envp)
{
	t_cmd_list	cmd_list;

	(void)argc;
	(void)argv;
	g_var.envp = get_envp(envp);
	while (1)
	{
		signal_setting();
		echoctl(0);
		if (!parse(&cmd_list))
		{
			g_var.exit_code = 1;
			continue ;
		}
		ft_execve(&cmd_list);
		free_cmd_list(&cmd_list);
	}
	return (0);
}
