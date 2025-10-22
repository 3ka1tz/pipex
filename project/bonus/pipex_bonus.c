/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez-u <elopez-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:41:02 by elopez-u          #+#    #+#             */
/*   Updated: 2025/01/09 12:58:37 by elopez-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	last_command(int infile_fd, int argc, char **argv, char **envp)
{
	int		outfile_fd;
	pid_t	last_pid;

	outfile_fd = open_output_file(argv[argc - 1], argv);
	if (outfile_fd == -1)
		error("Error: Opening output file failed");
	last_pid = fork();
	if (last_pid == -1)
		error("Error: Forking process for last command failed");
	if (last_pid == 0)
		handle_command(infile_fd, outfile_fd, argv[argc - 2], envp);
	close(infile_fd);
	close(outfile_fd);
}

void	execute_multiple_commands(int argc, char **argv, char **envp)
{
	int	pipe_fds[2];
	int	infile_fd;
	int	i;

	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		infile_fd = read_here_doc(argv[2]);
		i = 3;
	}
	else
	{
		infile_fd = open_input_file(argv[1]);
		i = 2;
	}
	while (i < argc - 2)
		pipe_and_fork(pipe_fds, &infile_fd, argv[i++], envp);
	last_command(infile_fd, argc, argv, envp);
	wait_for_all_processes();
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 4)
		error("Usage: ./pipex_bonus infile cmd1 ... cmdN outfile");
	execute_multiple_commands(argc, argv, envp);
	return (0);
}
