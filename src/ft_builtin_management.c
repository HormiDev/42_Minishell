/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_management.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:21:40 by dagimeno          #+#    #+#             */
/*   Updated: 2025/03/28 14:54:22 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_execute_builtin(t_cmd *cmd, t_minishell *minishell)
{
	ft_open_files(cmd, minishell);
	if (minishell->exit_code == 0)
	{
		if (!ft_strncmp_p(cmd->cmd, "cd", 3))
			ft_cd(cmd, minishell);
		else if (!ft_strncmp_p(cmd->cmd, "export", 6))
			ft_export_args(cmd, minishell);
		else if (!ft_strncmp_p(cmd->cmd, "unset", 5))
			ft_unset_args(&cmd->args[1], &minishell->envp, minishell);
		else if (!ft_strncmp_p(cmd->cmd, "env", 3))
			ft_print_env(minishell->envp, cmd->io_fd[1]);
		else if (!ft_strncmp_p(cmd->cmd, "exit", 4))
			ft_exit(&cmd->args[1], minishell);
		else if (!ft_strncmp_p(cmd->cmd, "echo", 4))
			ft_echo(cmd);
		else if (!ft_strncmp_p(cmd->cmd, "pwd", 3))
			ft_pwd(cmd, minishell);
	}
	ft_close_files(cmd);
}
