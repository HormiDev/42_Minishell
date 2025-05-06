/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_management_bonus.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:24:32 by dagimeno          #+#    #+#             */
/*   Updated: 2025/05/06 21:25:16 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_bonus.h"

int	ft_isbuiltin(char *command)
{
	if (!command)
		return (0);
	if (!ft_strncmp_p(command, "cd", 3)
		|| !ft_strncmp_p(command, "export", 7)
		|| !ft_strncmp_p(command, "unset", 6)
		|| !ft_strncmp_p(command, "env", 4)
		|| !ft_strncmp_p(command, "exit", 5)
		|| !ft_strncmp_p(command, "echo", 5)
		|| !ft_strncmp_p(command, "pwd", 4))
		return (1);
	return (0);
}

void	ft_execute_builtin(t_cmd *cmd, t_minishell *minishell)
{
	if (ft_open_files(cmd) != -1)
	{
		if (!ft_strncmp_p(cmd->cmd, "cd", 3))
			ft_cd(cmd, minishell);
		else if (!ft_strncmp_p(cmd->cmd, "export", 7))
			ft_export_args(cmd, minishell);
		else if (!ft_strncmp_p(cmd->cmd, "unset", 6))
			ft_unset_args(&cmd->args[1], &minishell->envp, minishell);
		else if (!ft_strncmp_p(cmd->cmd, "env", 4))
			ft_print_env(minishell->envp, cmd->io_fd[1], minishell);
		else if (!ft_strncmp_p(cmd->cmd, "exit", 5))
			ft_exit(&cmd->args[1], minishell);
		else if (!ft_strncmp_p(cmd->cmd, "echo", 5))
			ft_echo(cmd, minishell);
		else if (!ft_strncmp_p(cmd->cmd, "pwd", 4))
			ft_pwd(cmd, minishell);
	}
	else
		minishell->exit_code = 1;
	ft_close_files(cmd);
}
