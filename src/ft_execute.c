/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 21:37:58 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/05/06 23:00:30 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_pid_exit_with_error(void)
{
	if (errno == EACCES || errno == EISDIR || errno == ENOEXEC
		|| errno == ENAMETOOLONG)
		clean_and_exit(126);
	clean_and_exit(127);
}

static void	ft_dup_and_close(int file_fd, int new_fd)
{
	dup2(file_fd, new_fd);
	ft_close_alloc(file_fd);
}

void	ft_execute(t_cmd *cmd, t_minishell *minishell)
{
	char	*command;

	if (ft_open_files(cmd) == -1)
	{
		ft_close_pipes(minishell);
		clean_and_exit(1);
	}
	if (cmd->io_fd[0] != 0)
		ft_dup_and_close(cmd->io_fd[0], 0);
	if (cmd->io_fd[1] != 1)
		ft_dup_and_close(cmd->io_fd[1], 1);
	ft_close_pipes(minishell);
	if (ft_strchr(cmd->cmd, '/'))
		command = cmd->cmd;
	else
		command = ft_search_in_path(cmd->cmd, minishell);
	if (!command)
		clean_and_exit(127);
	execve(command, cmd->args, minishell->envp_array);
	perror(command);
	ft_pid_exit_with_error();
}
