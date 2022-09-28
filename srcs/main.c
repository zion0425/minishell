/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 14:15:39 by yjoo              #+#    #+#             */
/*   Updated: 2022/09/29 05:50:46 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	g_var.envp = envp;
	signal_setting();
    // char *str;

	t_cmd a;
	t_cmd b;
	t_cmd c;
	t_cmd_list list;
	
	a.type = WORD;
	a.cmd = "ls";
	a.next = &b;
	a.prev = 0;

	b.type = REDIROUT;
	b.cmd = ">";
	b.next = &c;
	b.prev = &a;

	c.type = WORD;
	c.cmd = "a";
	c.next = 0;
	c.prev = &b;


	list.head = &a;
	list.tail = &c;
	list.size = 0;

	ft_execve(&list);

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
