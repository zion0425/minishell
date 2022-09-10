/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 14:15:39 by yjoo              #+#    #+#             */
/*   Updated: 2022/09/10 15:07:27 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	//(void)envp;

	//char *str;
	while (1)
	{
		/*str = readline("minishell $> ");
			signal 
		if (str)
			ft_putstr_fd(ft_strjoin(str, "\n"), 1);
		else
			break ;
		add_history(str);
		free(str);*/
		while (*envp)
		{
			ft_putstr_fd(*envp++, 1);
			ft_putstr_fd("\n", 1);
		}
		if (!(*envp))
			break ;
	}
	return (0);
}
