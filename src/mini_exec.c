/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:44:42 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/04/01 20:19:50 by ide-dieg         ###   ########.fr       */
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

void	ft_pid_exit_with_error(void)
{
	ft_alloc_lst(0, 0);
	if (errno == EACCES || errno == EISDIR || errno == ENOEXEC
		|| errno == ENAMETOOLONG)
		exit(126);
	exit(127);
}

void	ft_execute(t_cmd *cmd, t_minishell *minishell)
{
	char	*command;
	char	**args;

	if (ft_open_files(cmd) == -1)
	{
		ft_close_pipes(minishell);
		ft_alloc_lst(0, 0);
		exit(1);
	}
	if (cmd->io_fd[0] != 0)
	{
		dup2(cmd->io_fd[0], 0);
		close(cmd->io_fd[0]);
	}
	if (cmd->io_fd[1] != 1)
	{
		dup2(cmd->io_fd[1], 1);
		close(cmd->io_fd[1]);
	}
	ft_close_pipes(minishell);
	if (ft_strchr(cmd->cmd, '/'))
		command = cmd->cmd;
	else
		command = ft_search_in_path(cmd->cmd, minishell);
	if (!command)
	{
		ft_alloc_lst(0, 0);
		exit(127);
	}
	args = cmd->args;
	execve(command, args, minishell->envp_array);
	perror(command);
	ft_pid_exit_with_error();
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
		ft_close_pipes(minishell);
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


void	ft_pipex_and_exec(t_minishell *mini, t_list *token_list)
{
	int		num_of_pipes;
	t_cmd	**commands_array;
	pid_t	*pids;
	int		i;
	int		last_exit_cmd_status;

	num_of_pipes = ft_pipe_counter(token_list);
	pids = ft_alloc_lst(sizeof(pid_t) * (num_of_pipes + 2), 4);
	commands_array = ft_cmd_array_converter(token_list);
	if (num_of_pipes  || !ft_isbuiltin((*commands_array)->cmd))
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
		ft_close_pipes(minishell);
		i = 0;
		while (pids[i])
		{
			waitpid(pids[i], &last_exit_cmd_status, 0);
			i++;
		}
		if (WIFSIGNALED(last_exit_cmd_status))
			minishell->exit_code = (128 + WTERMSIG(last_exit_cmd_status));
		if (WIFEXITED(last_exit_cmd_status))
			minishell->exit_code = (WEXITSTATUS(last_exit_cmd_status));
	}
	else
		ft_execute_builtin(*commands_array, minishell);
}
