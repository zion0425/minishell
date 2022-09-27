/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjoo <yjoo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:41:15 by yjoo              #+#    #+#             */
/*   Updated: 2022/09/27 05:24:24 by yjoo             ###   ########.fr       */
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

int	check_token(t_token *head_token, t_cmd_list *cmd_list)
{
	int		ret;
	t_token	*cur;

	ret = 0;
	cur = head_token;
	cmd_list->size = 1;
	while (cur->next)
	{
		if (cur->type == PIPE)
			cmd_list->size++;
		ret++;
		cur = cur->next;
	}
	return (ret);
}

/*int	create_parse_tree(t_cmd_list *cmd_list, t_token *head_token)
{
	int		token_cnt;

	token_cnt = check_token(head_token, cmd_list);
	//envp_convert(head_token, token_cnt);
	//dquote_dollar_to_word(head_token, NULL);
	return (1);
}*/

int	create_token_list(char *line, t_token **head_token)
{
	int	idx;

	idx = 0;
	while (line[idx])
	{
		while (line[idx] && (line[idx] == ' ' || \
		(line[idx] >= 9 && line[idx] <= 13)))
			idx++;
		if (!line[idx])
			return (0);
		if (!new_token(head_token, line, &idx))
			return (0);
		idx++;
	}
	return (1);
}

int	parse(t_cmd_list *cmd_list)
{
	char	*line;
	t_token	*head_token;

	(void)cmd_list;
	prompt(&line);
	if (is_empty(line, -1))
	{
		if (line)
			free(line);
		return (0);
	}
	head_token = NULL;
	if (!create_token_list(line, &head_token))
	{
		free_token_list(head_token);
		if (line)
			free(line);
		return (0);
	}
	//create_parse_tree(cmd_list, head_token);
	show_token_list(head_token);
	free_token_list(head_token);
	add_history(line);
	free(line);
	return (1);
}
