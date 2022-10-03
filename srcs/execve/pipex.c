/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 07:09:23 by siokim            #+#    #+#             */
/*   Updated: 2022/10/03 08:48:50 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pipe(char *tmp_cmd)
{
	int	pid;
	int	pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		ft_simplecmd(tmp_cmd);
	}
	else if (pid > 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		waitpid(pid, 0, 0);
	}
	else
		print_error("fork_error\n");
}
