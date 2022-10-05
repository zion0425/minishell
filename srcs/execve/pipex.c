/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 07:09:23 by siokim            #+#    #+#             */
/*   Updated: 2022/10/05 19:43:30 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_pipe(t_cmd **head, int start, int size)
{
	int	pid;
	int	pipefd[2];
	int	save_std[2];

	pipe(pipefd);
	pid = fork();
	set_stdfd(&save_std[0], &save_std[1], '0');
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		recursive_exec(head, start);
		exit(1);
	}
	else if (pid > 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		if (++start == size)
		{
			recursive_exec(head, start);
			return (set_stdfd(&save_std[0], &save_std[1], '0'));
		}
		ft_pipe(head, start, size);
	}
}
