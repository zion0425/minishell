/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siokim <siokim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 18:14:23 by siokim            #+#    #+#             */
/*   Updated: 2022/09/21 22:06:38 by siokim           ###   ########.fr       */
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
	waitpid(pid , 0, 0);
}

void	ft_execve(char **envp, t_node *node)
{
	if (node != NULL)
	{
		if (node->type == PIPE)
			ft_pipe(envp, node);
		else if (node->type <= 4 && node->type >= 1)
			ft_redirect(envp, node);
		else if (node->type == CMD)
			if ()
	}
	else if (node->right != NULL)
		ft_execve(node->right);
	else
		ft_cmd(envp, node);

}

void	ft_pipe(char **envp, t_node *node)
{
	int	pid;

	// 유효성 검사
	// pipe 앞에 cmd가 없을 경우 error
	// pipe 뒤에 cmd가 없을 경우 readline (pipe > ) 실행하여 cmd 값 추가 입력
	pid = fork();
	if (pid == 0)
		ft_execve(node->right);
	else if (pid > 0)
		ft_execve(node->left);
	else
		write(2, "fork_error\n", 11);


}

void	ft_echo()
{

}

void	ft_cd()
{

}

// bulit in 함수로 cd 구현시 pwd 경로를 잡아주는지 확인 필요.
void	ft_pwd();
void	ft_export();
void	ft_unset();
void	ft_env();
void	ft_exit();
