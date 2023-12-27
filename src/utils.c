/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siun <siun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:33:08 by subpark           #+#    #+#             */
/*   Updated: 2023/11/04 14:22:51 by siun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_2d(char **arr)
{
	static int	pipefd[2] = {-1, -1};
	int			i;

	i = 0;
	while (arr[i] != NULL)
		free(arr[i ++]);
	free(arr);
}

char	**paths_array(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(&envp[i][ft_strlen("PATH=")], ':'));
		i ++;
	}
	return (NULL);
}

char	*command_path(char **path_array, int i, char *command)
{
	char	*part_path;
	char	*path;

	part_path = ft_strjoin(path_array[i], "/");
	path = ft_strjoin(part_path, command);
	free(part_path);
	return (path);
}

char	*path_pointer(char **env, char *command)
{
	char	**path_array;
	char	*path;
	int		i;

	path_array = paths_array(env);
	i = 0;
	while (path_array[i] != NULL)
	{
		if (command[0] != '/')
			path = command_path(path_array, i, command);
		else
			path = ft_strdup(command);
		if (access(path, F_OK) == 0 && access(path, X_OK) == 0)
		{
			free_2d(path_array);
			return (path);
		}
		free(path);
		i ++;
	}
	free_2d(path_array);
	return (NULL);
}

void	print_error_cmd(char **env, char *command)
{
	char	*path_buf;
	char	**buf_command;

	buf_command = ft_split(command, ' ');
	if (!buf_command[0])
	{
		free_2d(buf_command);
		return ;
	}
	path_buf = path_pointer(env, buf_command[0]);
	if (!path_buf)
	{
		ft_printf("%s: ", buf_command[0]);
		if (errno != 2)
			perror("");
		else
			ft_printf("command not found\n");
	}
	free_2d(buf_command);
	free(path_buf);
	return ;
}
