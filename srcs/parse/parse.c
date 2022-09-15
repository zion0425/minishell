/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:41:15 by yjoo              #+#    #+#             */
/*   Updated: 2022/09/15 20:48:05 by yjoo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	prompt(char **line)
{
	*line = readline("minishell$> ");
	if (*line == NULL)
	{	
		ft_putstr_fd("\x1b[1A\033[12Cexit\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
}

int	get_token_type(char *line, int idx)
{
	if (line[idx] == '<')
	{
		if (line[idx + 1] && line[idx + 1] == '<')
			return (HEREDOC);
		return (REDIRIN);
	}
	else if (line[idx] == '>')
	{
		if (line[idx + 1] && line[idx + 1] == '>')
			return (APPEND);
		return (REDIROUT);
	}
	else if (line[idx] == '|')
		return (PIPE);
	else if (line[idx] == '\'')
		return (QUOTE);
	else if (line[idx] == '"')
		return (DQUOTE);
	else if (line[idx] == '$')
		return (DOLLAR);
	return (WORD);
}

char	*quote_token_handle(t_token	*new_token, char *line, int *idx)
{
	char	quote_type;

	quote_type = line[*idx];
	while (line[*idx] && line[*idx] != quote_type)
	{
		new_token->token = ft_strjoin("",line[*idx]);
		*idx++;
	}
	if (line[*idx] == '\0')
		return (NULL);
}

t_token	*new_token(char *line, int *idx)
{
	t_token	*new_token;

	new_token = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!new_token)
		return (NULL);
	new_token->type = get_token_type(line, *idx);
	if (new_token->type == HEREDOC || new_token->type == APPEND)
	{
		if (new_token->type == HEREDOC)
			new_token->token = ft_strdup("<<");
		if (new_token->type == APPEND)
			new_token->token = ft_strdup(">>");
		*idx++;
	}
	else if (new_token->type == REDIRIN)
		new_token->token = ft_strdup("<");
	else if (new_token->type == REDIRIN)
		new_token->token = ft_strdup("<");
	else if (new_token->type == REDIROUT)
		new_token->token = ft_strdup(">");
	else if (new_token->type == PIPE)
		new_token->token = ft_strdup("|");
	else if (new_token->type == DOLLAR)
		new_token->token = ft_strdup("$");
	else if (new_token->token == QUOTE || new_token->token == DQUOTE)
		new_token->token = quote_token_handle(new_token, line, idx);
	return (new_token);
}

int	create_token_list(char *line, t_token **token_head)
{
	int	idx;

	idx = 0;
	(void)token_head;
	while (line[idx])
	{
		while (line[idx] && (line[idx] == ' ' || \
		(line[idx] >= 9 && line[idx] <= 13)))
			idx++;
		if (!line[idx])
			return (0);
		if (!new_token(line, &idx))
			return (0);
	}
	return (1);
}

int	parse(void)
{
	char	*line;
	t_token	*token_head;

	prompt(&line);
	if (is_empty(line))
	{
		free(line);
		return (0);
	}
	if (!create_token_list(line, &token_head))
		return (0);
	add_history(line);
	free(line);
	return (1);
}
