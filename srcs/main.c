/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 14:15:39 by yjoo              #+#    #+#             */
/*   Updated: 2022/09/11 20:30:22 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	char *str;

	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	str = NULL;
	while (1)
	{
		str = readline("minishell$> ");
		if (str == NULL)
		{	
			ft_putstr_fd("\x1b[1A\033[12Cexit\n", 1);
			exit(EXIT_SUCCESS);
		}
		add_history(str);
		free(str);
	}
	return (0);
}
