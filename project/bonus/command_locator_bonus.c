/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_command_locator.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elopez-u <elopez-u@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:18:12 by elopez-u          #+#    #+#             */
/*   Updated: 2025/01/09 10:00:22 by elopez-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*get_env_path(char **envp)
{
	while (*envp)
	{
		if (ft_strncmp("PATH=", *envp, 5) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

static char	**get_dir_path(char **envp)
{
	char	*env_path;
	char	**dirs;

	env_path = get_env_path(envp);
	if (!env_path)
		return (NULL);
	dirs = ft_split(env_path, ':');
	if (!dirs)
		return (NULL);
	return (dirs);
}

static char	*search_cmd_in_dirs(char *cmd, char **dirs)
{
	char	*tmp;
	char	*cmd_path;

	if (!dirs)
		return (NULL);
	while (*dirs)
	{
		tmp = ft_strjoin(*dirs++, "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
	}
	return (NULL);
}

char	*get_command_path(char *cmd, char **envp)
{
	char	**dirs;
	char	*cmd_path;

	if (!cmd || !*cmd)
		return (NULL);
	dirs = get_dir_path(envp);
	if (!dirs)
		return (NULL);
	cmd_path = search_cmd_in_dirs(cmd, dirs);
	ft_free(dirs);
	return (cmd_path);
}
