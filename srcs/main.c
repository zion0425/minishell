/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 14:15:39 by yjoo              #+#    #+#             */
/*   Updated: 2022/09/10 19:20:49 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	char *str;
	while (1)
	{
		str = readline("minishell$> ");
		if (str)
		{
			ft_execve(envp, str);
			ft_putstr_fd(ft_strjoin(str, "\n"), 1);
		}
		else
		{
			break ;
		}
		add_history(str);
		free(str);
	}
	return (0);
}
