/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez-u <elopez-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:16:45 by elopez-u          #+#    #+#             */
/*   Updated: 2025/01/08 12:25:43 by elopez-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	open_output_file(const char *output_file)
{
	int	output_file_fd;

	output_file_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (output_file_fd == -1)
	{
		perror("Error: Opening output file failed");
		exit(1);
	}
	return (output_file_fd);
}

void	close_file(int *pipe_fds, int file_fd)
{
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	close(file_fd);
}
