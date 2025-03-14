/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:44:42 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/14 02:52:26 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


/*
<hoola <que >tal cat >adios
*/

void	ft_execution_fork(char *command, char **args, t_minishell *minishell)
{

	if (execve(command, args, minishell->envp_array) < 0)
	{
		ft_dprintf(2, "%s%s: %s%s\n", RED, command, strerror(errno), RESET);
		ft_alloc_lst(0, 0);
		exit(127);// revisar
	}
}

void	ft_execute_execve(char *command, char **args, t_minishell *minishell)
{
	int	id;
	int	exit_status;
	
	id = fork();
	if (id < 0)
	{
		ft_dprintf(2, "%s%s: %s%s\n", RED, "fork", strerror(errno), RESET);
		minishell->exit_code = 1;
		return ;
	}
	if (id == 0)
		ft_execution_fork(command, args, minishell);
	if (waitpid(id, &exit_status, 0) < 0)
	{
		ft_dprintf(2, "%s%s: %s%s\n", RED, "waitpid", strerror(errno), RESET);
		return ;
	}
	minishell->exit_code = WEXITSTATUS(exit_status);
}

void	ft_execute(char *command, char **args, t_minishell *minishell)
{
	char	*command_path;

	if (ft_strchr(command, '/'))
	{
		ft_execute_execve(command, args, minishell);
		return ;
	}
	command_path = ft_search_in_path(command, minishell);
	if (!command_path)
		return ;
	ft_execute_execve(command_path, args, minishell);
}

void	mini_exec(t_cmd *cmd, t_minishell *minishell)
{
	minishell->exit_code = 0;
	ft_open_files(cmd, minishell);
	if (cmd->cmd && minishell->exit_code == 0)
	{
		if (!ft_strncmp_p(cmd->cmd, "cd", 3))
			ft_cd(&cmd->args[1], &minishell->envp, minishell);
		else if (!ft_strncmp_p(cmd->cmd, "export", 6))
			ft_export_args(&cmd->args[1], &minishell->envp, minishell);
		else if (!ft_strncmp_p(cmd->cmd, "unset", 5))
			ft_unset_args(&cmd->args[1], &minishell->envp, minishell);
		else if (!ft_strncmp_p(cmd->cmd, "env", 3))
			ft_print_env(minishell->envp, minishell->io_fd[1]);
		else if (!ft_strncmp_p(cmd->cmd, "exit", 4))
			ft_exit(&cmd->args[1], minishell);
		else if (!ft_strncmp_p(cmd->cmd, "echo", 4))
			ft_echo(&cmd->args[1], minishell);
		else if (!ft_strncmp_p(cmd->cmd, "pwd", 3))
			ft_pwd(minishell);
		else
			ft_execute(cmd->cmd, cmd->args, minishell);
	}
	ft_close_files(minishell);
}
