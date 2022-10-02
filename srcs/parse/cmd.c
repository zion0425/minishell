/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:30:12 by yjoo              #+#    #+#             */
/*   Updated: 2022/10/03 04:23:36 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_vaild_cmd(t_cmd **head_cmd)
{
	t_cmd	*cur_cmd;

	cur_cmd = *head_cmd;
	while (cur_cmd)
	{
		if (cur_cmd->type >= REDIRIN && cur_cmd->type <= APPEND)
		{
			if (cur_cmd->next == NULL || \
			(cur_cmd->next->type >= REDIRIN && cur_cmd->next->type <= APPEND))
			{
				printf("syntax error near unexpected token\n");
				return (0);
			}
		}
		cur_cmd = cur_cmd->next;
	}
	return (1);
}

static int	get_cmd_type(t_token *token, char *cmd)
{
	int		idx;
	char	*tmp;

	idx = 0;
	tmp = ft_strdup(cmd);
	while (tmp[idx])
	{
		tmp[idx] = ft_tolower(tmp[idx]);
		idx++;
	}
	if (token->prev == NULL || token->prev->type == PIPE)
	{
		if (ft_strcmp(tmp, "echo") == 0 || ft_strcmp(tmp, "cd") == 0 || \
		ft_strcmp(tmp, "pwd") == 0 || ft_strcmp(tmp, "export") == 0 || \
		ft_strcmp(tmp, "unset") == 0 || ft_strcmp(tmp, "env") == 0 || \
		ft_strcmp(tmp, "exit") == 0)
		{
			free(tmp);
			return (BUILTIN);
		}
	}
	if (token->type == DQUOTE || token->type == QUOTE)
		return (WORD);
	free(tmp);
	return (token->type);
}

static int	add_cmd_list(t_cmd **head_cmd, t_cmd **new_cmd)
{
	t_cmd	*cur_cmd;

	if (*new_cmd == NULL)
		return (0);
	if (*head_cmd == NULL)
		*head_cmd = *new_cmd;
	else
	{
		cur_cmd = *head_cmd;
		while (cur_cmd->next != NULL)
			cur_cmd = cur_cmd->next;
		cur_cmd->next = *new_cmd;
		(*new_cmd)->prev = cur_cmd;
	}
	return (1);
}

int	new_cmd_list(t_cmd **head_cmd, t_token *head_token)
{
	t_cmd	*new_cmd;
	t_token	*cur_token;

	if (head_token == NULL)
		return (0);
	cur_token = head_token;
	while (cur_token && cur_token->type != PIPE)
	{
		new_cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
		if (!new_cmd)
			return (0);
		new_cmd->cmd = ft_strdup(cur_token->token);
		new_cmd->type = get_cmd_type(cur_token, new_cmd->cmd);
		if (!new_cmd->cmd || !add_cmd_list(head_cmd, &new_cmd))
			return (0);
		cur_token = cur_token->next;
	}
	if (!is_vaild_cmd(head_cmd))
		return (0);
	return (1);
}
