/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:14:23 by siokim            #+#    #+#             */
/*   Updated: 2022/10/02 22:00:54 by siokim           ###   ########.fr       */
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
void	recursive_exec(t_cmd_list *cmd_list, int size);
void	ft_pipe(t_cmd_list *cmd_list, int size)
{
	int	pid;
	int	pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		recursive_exec(cmd_list, size);
		exit(0);
	}
	else if (pid > 0)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		waitpid(pid, 0, 0);
	}
	else
		print_error("fork_error\n");
}

void	recursive_exec(t_cmd_list *cmd_list, int size)
{
	t_cmd	*node;
	char	*tmp_cmd;

	if (--size > 0)
		ft_pipe(cmd_list, size);
	node = cmd_list->head[size];
	while (node)
	{
		if (node->next != 0)
		{
			if (node->next->type >= REDIRIN && node->next->type <= HEREDOC)
			{
				ft_redirect(node);
				node = node->next->next;
			}
			else if (node->next->type == WORD)
			{
				tmp_cmd = node->cmd;
				while (node->next != 0 && node->type == WORD)
				{
					tmp_cmd =  ft_strjoin(tmp_cmd, ft_strjoin(" ",node->next->cmd));
					node = node->next;
				}
				ft_cmd(tmp_cmd);
				free(tmp_cmd);
			}
		}
		else
			ft_cmd(node->cmd);
		node = node->next;
	}
}

void	ft_execve(t_cmd_list *cmd_list)
{	
	int	size;

	size = cmd_list->size;
	recursive_exec(cmd_list, size);
}