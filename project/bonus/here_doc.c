/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez-u <elopez-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:05:36 by elopez-u          #+#    #+#             */
/*   Updated: 2025/01/09 12:04:22 by elopez-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	is_here_doc(char *arg)
{
	return (ft_strcmp(arg, "here_doc") == 0);
}

static void	read_and_write_to_pipe(int fd[2], char *delimiter)
{
	char	*line;

	close(fd[0]);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	exit(0);
}

int	read_here_doc(char *delimiter)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error("Error: Pipe creation failed");
	pid = fork();
	if (pid == -1)
		error("Error: Forking process for here_doc failed");
	if (pid == 0)
		read_and_write_to_pipe(fd, delimiter);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	return (fd[0]);
}
