/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:14:23 by siokim            #+#    #+#             */
/*   Updated: 2022/09/22 16:15:33 by siokim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*getpath(char **envp, char *cmd)
{
	int			i;
	char		*path;
	char		**paths;
	char		*res_path;
	struct stat	buf;

	i = -1;
	while (envp[++i] != NULL)
		if (!ft_strncmp(envp[i], "PATH=", 5))
			break ;
	if (ft_strchr(cmd, '/') || envp[i] == NULL)
		return (cmd);
	path = &envp[i][5];
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

void	ft_cmd(char **envp, char *cmd)
{
	char	*path;
	char	**cmds;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		cmds = ft_split(cmd, ' ');
		path = getpath(envp, cmds[0]);
		execve(path, cmds, envp);
		write(2, cmd, ft_strlen(cmd));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	waitpid(pid, 0, 0);
}

void	ft_execve(char **envp, t_node *node)
{
	if (node != NULL)
	{
		if (node->type == PIPE)
			ft_pipe(envp, node);
		else if (node->type <= 4 && node->type >= 1)
			ft_redirect(envp, node);
		else if (node->type == COMMAND_LIST)
			ft_cmd(envp, node->/*name*/);
	}
	else if (node->right != NULL)
		ft_execve(node->right);
}

void	ft_pipe(char **envp, t_node *node)
{
	int	pid;
	int	pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		ft_execve(node->left);
	}
	else if (pid > 0)
	{
		waitpid(pid, 0, 0);
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		ft_execve(node->right);
	}
	else
		print_error("fork_error\n");
}
