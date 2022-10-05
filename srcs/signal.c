/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 16:37:19 by yjoo              #+#    #+#             */
/*   Updated: 2022/10/06 07:55:19 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	sigint_handler(int signo)
{
	pid_t	pid;

	pid = waitpid(-1, NULL, WNOHANG);
	if (signo == SIGINT)
	{
		if (pid == -1)
		{
			g_var.exit_code = 1;
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
		{
			g_var.exit_code = 130;
			printf("\n");
		}
	}
}

static void	sigquit_handler(int signo)
{
	pid_t	pid;

	pid = waitpid(-1, NULL, WNOHANG);
	if (signo == SIGQUIT)
	{
		if (pid == -1)
		{
			rl_on_new_line();
			rl_redisplay();
		}
		else
		{
			g_var.exit_code = 131;
			printf("Quit: %d\n", signo);
		}
	}
}

static void	ft_heredoc_signal(int signo)
{
	(void)signo;
	ft_putendl_fd("", 1);
	exit(1);
}

void	signal_setting(int option)
{
	if (option == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, sigquit_handler);
		signal(SIGINT, sigint_handler);
	}
	if (option == 1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, ft_heredoc_signal);
	}
	if (option == 2)
	{
		signal(SIGQUIT, SIG_IGN);
	}
}
