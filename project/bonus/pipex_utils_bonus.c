/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez-u <elopez-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:16:45 by elopez-u          #+#    #+#             */
/*   Updated: 2025/01/09 12:05:07 by elopez-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	error(const char *msg)
{
	if (msg)
		perror(msg);
	exit(EXIT_FAILURE);
}

int	open_input_file(const char *input_file)
{
	int	input_file_fd;

	input_file_fd = open(input_file, O_RDONLY);
	if (input_file_fd == -1)
	{
		perror("Warning: Error opening input file, using /dev/null");
		input_file_fd = open("/dev/null", O_RDONLY);
		if (input_file_fd == -1)
			error("Error: Opening /dev/null failed");
	}
	return (input_file_fd);
}

int	open_output_file(char *output_file, char **argv)
{
	int	outfile_fd;

	if (ft_strcmp(argv[1], "here_doc") == 0)
		outfile_fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		outfile_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd == -1)
		error("Error: Opening output file failed");
	return (outfile_fd);
}

void	close_file(int *pipe_fds, int file_fd)
{
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	close(file_fd);
}

void	wait_for_all_processes(void)
{
	int	status;

	while (wait(&status) > 0)
		;
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	exit(1);
}
