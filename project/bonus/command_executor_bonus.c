/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executor_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez-u <elopez-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:43:23 by elopez-u          #+#    #+#             */
/*   Updated: 2025/01/09 11:06:02 by elopez-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_cmd_args(char	**cmd_args)
{
	size_t	i;

	if (!cmd_args)
		return ;
	i = 0;
	while (cmd_args[i])
		free(cmd_args[i++]);
	free(cmd_args);
}

void	execute_command(char *argv, char **envp)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(argv, ' ');
	if (!cmd_args)
		error("Error: Command splitting failed");
	cmd_path = get_command_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		free_cmd_args(cmd_args);
		perror("Error: Command not found");
		exit(127);
	}
	if (execve(cmd_path, cmd_args, envp) == -1)
	{
		free_cmd_args(cmd_args);
		free(cmd_path);
		perror("Error: Execution failed");
		exit(126);
	}
}

void	handle_command(int infile_fd, int outfile_fd, char *cmd, char **envp)
{
	if (dup2(infile_fd, STDIN_FILENO) == -1
		|| dup2(outfile_fd, STDOUT_FILENO) == -1)
		error("Error: Setting up pipes failed");
	close(infile_fd);
	close(outfile_fd);
	execute_command(cmd, envp);
}

void	pipe_and_fork(int *pipe_fds, int *infile_fd, char *cmd, char **envp)
{
	pid_t	pid;

	if (pipe(pipe_fds) == -1)
		error("Error: Pipe creation failed");
	pid = fork();
	if (pid == -1)
		error("Error: Forking process failed");
	if (pid == 0)
	{
		close(pipe_fds[0]);
		handle_command(*infile_fd, pipe_fds[1], cmd, envp);
	}
	close(*infile_fd);
	close(pipe_fds[1]);
	*infile_fd = pipe_fds[0];
}
