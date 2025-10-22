/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez-u <elopez-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:35:29 by elopez-u          #+#    #+#             */
/*   Updated: 2025/01/08 12:11:47 by elopez-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_check_line_jump(char *new_str)
{
	if (!new_str)
		return (0);
	while (*new_str)
	{
		if (*new_str == '\n')
			return (1);
		new_str++;
	}
	return (0);
}

ssize_t	read_from_fd(int fd, char **buffer)
{
	char	*temp_buffer;
	ssize_t	bytes_read;
	char	*new_buffer;

	temp_buffer = malloc(BUFFER_SIZE + 1);
	if (!temp_buffer)
		return (-1);
	bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(temp_buffer);
		return (-1);
	}
	temp_buffer[bytes_read] = '\0';
	new_buffer = ft_strjoin(*buffer, temp_buffer);
	free(temp_buffer);
	if (!new_buffer)
	{
		free(*buffer);
		return (-1);
	}
	free(*buffer);
	*buffer = new_buffer;
	return (bytes_read);
}

char	*extract_line(char **buffer)
{
	char	*new_line_pos;
	size_t	line_len;
	char	*line;
	char	*new_buffer;

	if (!*buffer || !**buffer)
		return (NULL);
	new_line_pos = ft_strchr(*buffer, '\n');
	if (new_line_pos)
		line_len = (new_line_pos - *buffer) + 1;
	else
		line_len = (ft_strlen(*buffer));
	line = malloc(line_len + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, *buffer, line_len + 1);
	if (new_line_pos)
		new_buffer = ft_strdup(new_line_pos + 1);
	else
		new_buffer = NULL;
	free(*buffer);
	*buffer = new_buffer;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD];
	ssize_t		bytes_read;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	while (!ft_check_line_jump(buffer[fd]))
	{
		bytes_read = read_from_fd(fd, &buffer[fd]);
		if (bytes_read < 0)
		{
			free(buffer[fd]);
			buffer[fd] = NULL;
			return (NULL);
		}
		if (bytes_read == 0)
			break ;
	}
	line = extract_line(&buffer[fd]);
	if (!line && buffer[fd])
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	return (line);
}
