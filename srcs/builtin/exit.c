/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 04:49:31 by yjoo              #+#    #+#             */
/*   Updated: 2022/10/06 06:26:12 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	exit_msg(char *str, int code, int isexit)
{
	g_var.exit_code = code;
	if (isexit == 1)
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd(str, 1);
		exit(g_var.exit_code);
	}
	ft_putstr_fd(str, 1);
	return ;
}

static int	get_argc(t_cmd *cmd)
{
	int		ret;
	t_cmd	*cur;

	cur = cmd;
	ret = 0;
	while (cur)
	{
		ret++;
		cur = cur->next;
	}
	return (ret);
}

static int	ft_isdigits(char *str)
{
	size_t	size;

	size = ft_strlen(str);
	while (size--)
		if (!ft_isdigit(str[size]))
			return (1);
	return (0);
}

void	none_pipe(t_cmd **node, int argc)
{
	if (argc == 1)
		exit_msg("", g_var.exit_code, 1);
	else if (argc == 2 && !ft_isdigits((*node)->cmd))
		exit_msg("", g_var.exit_code, 1);
	else if (argc >= 2 && ft_isdigits((*node)->cmd))
		exit_msg("minishell: exit: numeric argument required\n", 1, 1);
	else if (argc >= 3)
		exit_msg("minishell: exit: too many arguments\n", 255, 0);
}

void	ft_exit(t_cmd **node, int size)
{
	int		argc;

	argc = get_argc(*node);
	(*node) = (*node)->next;
	if (size == 0)
		none_pipe(node, argc);
	else if (size >= 1)
	{
		if (argc == 1)
			exit_msg("", g_var.exit_code, 0);
		else if (argc == 2 && !ft_isdigits((*node)->cmd))
			exit_msg("", g_var.exit_code, 0);
		else if (argc >= 2 && ft_isdigits((*node)->cmd))
			exit_msg("minishell: exit: numeric argument required\n", 1, 0);
		else if (argc >= 3)
			exit_msg("minishell: exit: too many arguments\n", 255, 0);
	}
	while (--argc > 0)
		(*node) = (*node)->next;
}
