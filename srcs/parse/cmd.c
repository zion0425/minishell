/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 17:30:12 by yjoo              #+#    #+#             */
/*   Updated: 2022/10/02 20:15:35 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	get_cmd_type(t_token *token, char *cmd)
{
	if (token->prev == NULL || token->prev->type == PIPE)
	{
		if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0 || \
		ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0 || \
		ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0 || \
		ft_strcmp(cmd, "exit") == 0)
			return (BUILTIN);
	}
	if (token->type == DQUOTE || token->type == QUOTE)
		return (WORD);
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
	return (1);
}
