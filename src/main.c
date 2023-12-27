/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siun <siun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:46:31 by subpark           #+#    #+#             */
/*   Updated: 2023/11/04 14:22:34 by siun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec(char *cmd, char **env)
{
	char	**command;
	char	*path;

	command = ft_split(cmd, ' ');
	if (!command)
		exit(errno);
	if (!command[0])
	{
		free_2d(command);
		exit(2);
	}
	path = path_pointer(env, command[0]);
	if (!path)
	{
		free_2d(command);
		free(path);
		exit(2);
	}
	execve(path, command, env);
	if (path)
		free(path);
	free_2d(command);
	exit (errno);
}

void	first_action(int *pip, int *pipefd, char *cmd, char **envp)
{
	int	fd[2];

	fd[0] = dup2(pip[0], 0);
	fd[1] = dup2(pipefd[1], 1);
	if (fd[0] == -1 || fd[1] == -1)
	{
		close(fd[0]);
		close(fd[1]);
		close(pipefd[0]);
		exit (errno);
		return ;
	}
	close(pipefd[0]);
	exec(cmd, envp);
	exit(2);
}

void	second_action(int *pip, int *pipefd, char *cmd, char **envp)
{
	int	fd[2];

	if (pipefd[1] < 0)
		exit(1);
	fd[1] = dup2(pip[1], 1);
	fd[0] = dup2(pipefd[0], 0);
	if (fd[0] == -1 || fd[1] == -1)
	{
		close(fd[1]);
		close(fd[0]);
		close(pipefd[1]);
		exit (errno);
	}
	close(pipefd[1]);
	exec(cmd, envp);
	exit(2);
}

void	pipex(int *pip, char *cmd1, char *cmd2, char **envp)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (perror("Pipe: "));
	pid = fork();
	if (pid < 0)
		return (perror("Fork: "));
	else if (pid == 0)
		first_action(pip, pipefd, cmd1, envp);
	else
	{
		waitpid(pid, NULL, WNOHANG);
		second_action(pip, pipefd, cmd2, envp);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	pip[2];

	if (argc != 5)
	{
		ft_printf("Error: Bad arguments\n");
		exit(1);
	}
	pip[0] = open(argv[1], O_RDONLY);
	pip[1] = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (pip[0] < 3)
	{
		if (pip[0] < 0)
			ft_printf("bash: %s: ", argv[1]);
		perror("");
	}
	if (pip[1] < 3)
	{
		if (pip[1] < 0)
			ft_printf("bash: %s: ", argv[argc - 1]);
		perror("");
	}
	print_error_cmd(envp, argv[2]);
	print_error_cmd(envp, argv[argc -2]);
	pipex(pip, argv[2], argv[3], envp);
	return (0);
}
