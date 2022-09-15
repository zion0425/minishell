/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 14:15:39 by yjoo              #+#    #+#             */
/*   Updated: 2022/09/15 15:11:28 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	char *str;
	while (1)
	{
		str = readline("minishell$> ");
		if (str)
		{
			ft_cmd(envp, str);
			
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
