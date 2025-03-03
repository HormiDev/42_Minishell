/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:44:42 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/03 17:49:57 by ide-dieg         ###   ########.fr       */
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

	if (ft_strchr(command, '/') && !access(command, X_OK))
	{
		ft_execute_execve(command, args, minishell);
		return ;
	}
	command_path = ft_search_in_path(command, minishell);
	if (!command_path)
		return ;
	ft_execute_execve(command_path, args, minishell);
}

void	mini_exec(char *command, char **args, t_minishell *minishell)
{
	minishell->exit_code = 0;
	if (!ft_strncmp_p(command, "cd", 3))
		ft_cd(&args[1], &minishell->envp, minishell);
	else if (!ft_strncmp_p(command, "export", 6))
		ft_export_args(&args[1], &minishell->envp, minishell);
	else if (!ft_strncmp_p(command, "unset", 5))
		ft_unset_args(&args[1], &minishell->envp, minishell);
	else if (!ft_strncmp_p(command, "env", 3))
		ft_print_env(minishell->envp);
	else if (!ft_strncmp_p(command, "exit", 4))
		ft_exit(&args[1], minishell);
	else if (!ft_strncmp_p(command, "echo", 4))
		ft_echo(&args[1]);
	else if (!ft_strncmp_p(command, "pwd", 3))
		ft_pwd(minishell);
	else
		ft_execute(command, args, minishell);
}
