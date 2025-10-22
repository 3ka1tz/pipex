/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez-u <elopez-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:38:39 by elopez-u          #+#    #+#             */
/*   Updated: 2025/01/13 10:50:06 by elopez-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <unistd.h>

# include "../libft/libft.h"

// utils.c
void	error(const char *msg);
int		open_input_file(const char *input_file);
int		open_output_file(const char *output_file);
void	close_file(int *pipe_fds, int file_fd);

// command_locator.c
char	*get_command_path(char *cmd, char **envp);

// command_executor.c
void	execute_first_command(char **argv, char **envp, int *pipe_fds);
void	execute_second_command(char **argv, char **envp, int *pipe_fds);

#endif