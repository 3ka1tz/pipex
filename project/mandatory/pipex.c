/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez-u <elopez-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:38:21 by elopez-u          #+#    #+#             */
/*   Updated: 2025/01/13 10:52:15 by elopez-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fds[2];
	pid_t	pid;

	if (argc != 5)
		error("Usage: ./pipex infile cmd1 cmd2 outfile");
	if (pipe(pipe_fds) == -1)
		error("Error: Pipe creation failed");
	pid = fork();
	if (pid == -1)
		error("Error: Forking process failed");
	if (pid == 0)
		execute_first_command(argv, envp, pipe_fds);
	else
	{
		execute_second_command(argv, envp, pipe_fds);
	}
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	return (0);
}

//if (waitpid(pid, NULL, 0) == -1)
	//error("Error waiting for child process");