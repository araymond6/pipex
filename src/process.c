/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: araymond <araymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:17:35 by araymond          #+#    #+#             */
/*   Updated: 2023/03/24 16:24:16 by araymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

// Goes through all paths and access() with arg_cmd.
char	*access_cmd(t_pipex *s_pipex, char **arg_cmd)
{
	int		i;
	char	*cmd;

	i = 0;
	while (s_pipex->paths[i])
	{
		cmd = join_command(s_pipex->paths[i], arg_cmd[0]);
		if (!cmd)
			error_message(s_pipex);
		if (access(cmd, X_OK | F_OK) == 0)
			return (cmd);
		free(cmd);
		i++;
	}
	return (NULL);
}

// Executes command.
void	exec_cmd(t_pipex *s_pipex, char **arg_cmd)
{
	char	*cmd;

	cmd = access_cmd(s_pipex, arg_cmd);
	if (!cmd)
		error_message(s_pipex);
	execve(cmd, arg_cmd, NULL);
}

// Handles the first command.
void	child_one(t_pipex *s_pipex)
{
	dup2(s_pipex->fds[0], STDIN_FILENO);
	dup2(s_pipex->pipe[1], STDOUT_FILENO);
	close_fds(s_pipex->pipe);
	close_fds(s_pipex->fds);
	exec_cmd(s_pipex, s_pipex->cmd1);
}

// Handles the second command.
void	child_two(t_pipex *s_pipex)
{
	dup2(s_pipex->pipe[0], STDIN_FILENO);
	dup2(s_pipex->fds[1], STDOUT_FILENO);
	close_fds(s_pipex->pipe);
	close_fds(s_pipex->fds);
	exec_cmd(s_pipex, s_pipex->cmd2);
}

// Start of pipe, fork and child processes.
void	pipe_process(t_pipex *s_pipex)
{
	int		status;

	open_files(s_pipex);
	if (pipe(s_pipex->pipe) == -1)
		error_message(s_pipex);
	s_pipex->child[0] = fork();
	if (s_pipex->child[0] < 0)
		error_message(s_pipex);
	if (s_pipex->child[0] == 0)
		child_one(s_pipex);
	s_pipex->child[1] = fork();
	if (s_pipex->child[1] < 0)
		error_message(s_pipex);
	if (s_pipex->child[1] != 0)
		child_two(s_pipex);
	close_fds(s_pipex->fds);
	close_fds(s_pipex->pipe);
	waitpid(s_pipex->child[0], &status, 0);
	waitpid(s_pipex->child[1], &status, 0);
}
