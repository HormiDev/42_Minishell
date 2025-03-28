/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:44:42 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/28 19:54:41 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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


void	ft_execute(t_cmd *cmd, t_minishell *minishell)
{
	char	*command;
	char	**args;

	dup2(cmd->io_fd[0], 0);
	dup2(cmd->io_fd[1], 1);
	ft_open_files(cmd, minishell);
	command = ft_search_in_path(cmd->cmd, minishell);
	if (!command)
	{
		ft_dprintf(2, "%s%s: command not found%s\n", RED, cmd->cmd, RESET);
		minishell->exit_code = 127;
		exit(127);
	}
	args = cmd->args;
	execve(command, args, minishell->envp_array);
	exit(127);
}

int	ft_isbuiltin(char *command)
{
	if (!ft_strncmp_p(command, "cd", 3)
		|| !ft_strncmp_p(command, "export", 6)
		|| !ft_strncmp_p(command, "unset", 5)
		|| !ft_strncmp_p(command, "env", 3)
		|| !ft_strncmp_p(command, "exit", 4)
		|| !ft_strncmp_p(command, "echo", 4)
		|| !ft_strncmp_p(command, "pwd", 3))
		return (1);
	return (0);
}

void	mini_exec(t_cmd *cmd, t_minishell *minishell)
{
	if (ft_isbuiltin(cmd->cmd))
	{
		ft_execute_builtin(cmd, minishell);
		exit(minishell->exit_code);
	}
	else
		ft_execute(cmd, minishell);
}

t_cmd	**ft_cmd_array_converter(t_list *token_list)
{
	t_cmd	**commands_array;
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = token_list;
	while (tmp)
	{
		if (((t_data_container *)tmp->content)->type == 0)
			i++;
		tmp = tmp->next;
	}
	commands_array = ft_alloc_lst((i + 1) * sizeof(t_cmd *), 4);
	i = 0;
	tmp = token_list;
	while (tmp)
	{
		if (((t_data_container *)tmp->content)->type == 0)
		{
			commands_array[i] = (t_cmd *)((t_data_container *)tmp->content)->data;
			i++;
		}
		tmp = tmp->next;
	}
	return (commands_array);
}


void	ft_pipex_and_exec(t_minishell *minishell, t_list *token_list)
{
	int		num_of_pipes;
	t_cmd	**commands_array;
	pid_t	*pids;
	int		i;

	num_of_pipes = ft_pipe_counter(token_list);
	pids = ft_alloc_lst(sizeof(pid_t) * (num_of_pipes + 2), 4);
	commands_array = ft_cmd_array_converter(token_list);
	if (num_of_pipes)
	{
		i = 0;
		ft_pipeline(minishell, commands_array, num_of_pipes);
		while(commands_array[i])
		{
			pids[i] = fork();
			if (pids[i] < 0)
			{
				ft_dprintf(2, "%s%s: %s%s\n", RED, "fork", strerror(errno), RESET);
				minishell->exit_code = 1;
				return ;
			}
			else if (pids[i] == 0)
				mini_exec(commands_array[i], minishell);
			i++;
		}
	}
	else if (ft_isbuiltin((*commands_array)->cmd))
		ft_execute_builtin(*commands_array, minishell);
	else
		ft_execute(*commands_array, minishell);// crear un fork o mober al bucle
}
