/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: siun <siun@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 11:33:24 by subpark           #+#    #+#             */
/*   Updated: 2023/10/10 16:13:46 by siun             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>
# include <errno.h>

void	pipex(int *pip, char *cmd1, char *cmd2, char **envp);
void	first_action(int *pip, int *pipefd, char *cmd, char **envp);
void	second_action(int *pip, int *pipefd, char *cmd, char **envp);
void	exec(char *cmd, char **env);
void	free_2d(char **arr);
char	**paths_array(char **envp);
char	*path_pointer(char **env, char *command);
void	print_error_cmd(char **env, char *command);

#endif