/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez-u <elopez-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:38:39 by elopez-u          #+#    #+#             */
/*   Updated: 2025/01/09 12:44:42 by elopez-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

# include "get_next_line_bonus/get_next_line_bonus.h"

// command_locator.c
char	*get_command_path(char *cmd, char **envp);

// command_executor.c
void	execute_command(char *argv, char **envp);
void	handle_command(int infile_fd, int outfile_fd, char *cmd, char **envp);
void	pipe_and_fork(int *pipe_fds, int *infile_fd, char *cmd, char **envp);

// pipex_utils_bonus.c
void	error(const char *msg);
int		open_input_file(const char *input_file);
int		open_output_file(char *output_file, char **argv);
void	close_file(int *pipe_fds, int file_fd);
void	wait_for_all_processes(void);

// here_doc.c
int		is_here_doc(char *arg);
int		read_here_doc(char *delimiter);

#endif