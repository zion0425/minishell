/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:14:23 by siokim            #+#    #+#             */
/*   Updated: 2022/10/03 04:21:36 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*getpath(char *cmd)
{
	int			i;
	char		*path;
	char		**paths;
	char		*res_path;
	struct stat	buf;

	i = -1;
	while (g_var.envp[++i] != NULL)
		if (!ft_strncmp(g_var.envp[i], "PATH=", 5))
			break ;
	if (ft_strchr(cmd, '/') || g_var.envp[i] == NULL)
		return (cmd);
	path = &g_var.envp[i][5];
	paths = ft_split(path, ':');
	i = -1;
	while (paths[++i])
	{
		res_path = ft_strjoin(ft_strjoin(paths[i], "/"), cmd);
		if (stat(res_path, &buf) != -1)
			return (res_path);
		free(res_path);
	}
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	exit(127);
}

void	ft_cmd(char *cmd)
{
	char	*path;
	char	**cmds;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		cmds = ft_split(cmd, ' ');
		path = getpath(cmds[0]);
		execve(path, cmds, g_var.envp);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	waitpid(pid, 0, 0);
}
// void	recursive_exec(t_cmd **head, int size);

// void	ft_pipe(t_cmd_list *cmd_list, int size)
// {
// 	int	pid;
// 	int	pipefd[2];

// 	pipe(pipefd);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		close(pipefd[0]);
// 		dup2(pipefd[1], STDOUT_FILENO);
// 		if (size > 0)
// 			ft_pipe(cmd_list, --size);
// 	}
// 	else if (pid > 0)
// 	{
// 		close(pipefd[1]);
// 		dup2(pipefd[0], STDIN_FILENO);
// 		waitpid(pid, 0, 0);
// 	}
// 	else
// 		print_error("fork_error\n");
// 	recursive_exec(cmd_list->head, size);	
// }

char	*get_cmds(t_cmd **node)
{
	char	*tmp_cmd;

	tmp_cmd = (*node)->cmd;
	while ((*node)->next != 0 && (*node)->next->type == WORD)
	{
		tmp_cmd =  ft_strjoin(tmp_cmd, ft_strjoin(" ",(*node)->next->cmd));
		(*node) = (*node)->next;
	}
	return (tmp_cmd);
}

void	recursive_exec(t_cmd **head, int size)
{
	t_cmd	*node;
	char	*tmp_cmd;
	int		save_stdout;
	int		save_stdin;

	save_stdout = dup(1);
	save_stdin = dup(0);
	size = 0;
	node = head[size];
	ft_redirect(node);
	while (node)
	{
		if (node->type == WORD)
			tmp_cmd = get_cmds(&node);
		if (node->type >= REDIRIN && node->type <= APPEND)
			node=node->next;
		ft_cmd(tmp_cmd);
		if (node->type == WORD)
			break;
		node = node->next;
	}
	dup2(save_stdout, 1);
	dup2(save_stdin, 0);

}

void	ft_execve(t_cmd_list *cmd_list)
{	
	int	size;
	int	i;

	i = -1;
	size = cmd_list->size;

	recursive_exec(cmd_list->head, size);
}