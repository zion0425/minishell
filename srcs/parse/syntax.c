/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 06:55:29 by yjoo              #+#    #+#             */
/*   Updated: 2022/09/25 16:05:31 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	syntax_pipe(t_token *token)
{
	syntax_cmd(token);
	if (token->type == PIPE)
		syntax_pipe(token);
}

void	syntax_cmd(t_token *token)
{
	syntax_simple_cmd(token);
	if (token->type >= REDIRIN && token->type <= APPEND)
		syntax_redir(token);
}

void	syntax_redir(t_token *token)
{
	if (token->type >= REDIRIN && token->type <= APPEND)
	{
		if (token->next->type == WORD)
			;
		else
			;
	}
	if (token->type >= REDIRIN && token->type <= APPEND)
		syntax_redir(token);
}

void	syntax_simple_cmd(t_token *token)
{
	if (token->type == WORD)
	{
		if (token->type == WORD)
			;
	}
	else
		;
}
