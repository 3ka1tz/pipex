/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_executor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez-u <elopez-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:43:23 by elopez-u          #+#    #+#             */
/*   Updated: 2025/01/08 12:14:47 by elopez-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	execute_first_command(char **argv, char **envp, int *pipe_fds)
{
	int		input_file_fd;

	input_file_fd = open_input_file(argv[1]);
	if (dup2(pipe_fds[1], STDOUT_FILENO) == -1)
		error("Error: Redirecting pipe write end to stdout failed");
	if (dup2(input_file_fd, STDIN_FILENO) == -1)
		error("Error: Redirecting input file to stdin failed");
	close_file(pipe_fds, input_file_fd);
	execute_command(argv[2], envp);
}

void	execute_second_command(char **argv, char **envp, int *pipe_fds)
{
	int	output_file_fd;

	output_file_fd = open_output_file(argv[4]);
	if (dup2(pipe_fds[0], STDIN_FILENO) == -1)
		error("Error: Redirecting pipe read end to stdin failed");
	if (dup2(output_file_fd, STDOUT_FILENO) == -1)
		error("Error: Redirecting stdout to output file failed");
	close_file(pipe_fds, output_file_fd);
	execute_command(argv[3], envp);
}
