/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 14:15:39 by yjoo              #+#    #+#             */
/*   Updated: 2022/09/22 19:17:58 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	
	t_cmd	node1;
	t_cmd	node2;
	t_cmd	node3;
	t_cmd	node4;
	t_cmd	node6;
	node1.cmd = "|";
	node1.left = &node2;
	node1.right = &node6;
	node1.type = PIPE;
	
	node2.cmd = ">";
	node2.left = &node3;
	node2.right = &node4;
	node2.type = REDIROUT;
	
	node3.cmd = "ls -al";
	node3.left = NULL;
	node3.right = NULL;
	node3.type = WORD;

	node4.cmd = "a.txt";
	node4.left = NULL;
	node4.right = NULL;
	node4.type = WORD;
	
	node6.cmd = "wc -l";
	node6.left = NULL;
	node6.right = NULL;
	node6.type = WORD;

	signal_setting();
    // char *str;
	ft_execve(envp, &node1);

    // while(1)
    // {
    //     str = readline("minishell$> ");
    //     if (str)
    //     else
    //         break ;
    //     add_history(str);
    //     free(str);
    // }
	return (0);
}
