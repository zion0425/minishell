/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 13:41:15 by yjoo              #+#    #+#             */
/*   Updated: 2022/10/05 19:47:32 by siokim           ###   ########.fr       */
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

static int	check_token(t_token *head_token, t_cmd_list *cmd_list)
{
	int		ret;
	t_token	*cur;

	ret = 0;
	cur = head_token;
	cmd_list->size = 1;
	while (cur)
	{
		if (cur->type == PIPE)
		{
			cmd_list->size++;
			if (cur->next == NULL)
			{
				printf("invaild pipe\n");
				return (0);
			}
		}
		ret++;
		cur = cur->next;
	}
	return (ret);
}

static int	create_cmd_list(t_cmd_list *cmd_list, t_token *head_token)
{
	int		token_cnt;
	int		idx;
	t_token	*cur_token;

	token_cnt = check_token(head_token, cmd_list);
	if (token_cnt == 0)
		return (0);
	idx = 0;
	if (!envp_convert(head_token, token_cnt))
		return (0);
	cmd_list->head = (t_cmd **)ft_calloc(cmd_list->size, sizeof(t_cmd *));
	if (!cmd_list->head)
		return (0);
	cur_token = head_token;
	while (idx < cmd_list->size)
	{
		if (!new_cmd_list(&cmd_list->head[idx], cur_token))
			return (0);
		cur_token = search_token(cur_token, PIPE)->next;
		// show_cmd(&cmd_list->head[idx]);
		idx++;
	}
	return (1);
}

static int	create_token_list(char *line, t_token **head_token)
{
	int	idx;

	idx = 0;
	while (line[idx])
	{
		while (line[idx] && (line[idx] == ' ' || \
		(line[idx] >= 9 && line[idx] <= 13)))
			idx++;
		if (!line[idx])
			return (1);
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
	if (is_empty(line))
	{
		if (line)
			free(line);
		return (0);
	}
	add_history(line);
	head_token = NULL;
	if (!create_token_list(line, &head_token))
	{
		free_token_list(head_token, line);
		return (0);
	}
	if (!create_cmd_list(cmd_list, head_token))
	{
		free_token_list(head_token, line);
		return (0);
	}
	free_token_list(head_token, line);
	return (1);
}
