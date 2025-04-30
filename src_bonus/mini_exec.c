/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:44:42 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/04/30 18:16:42 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	mini_exec(t_cmd *cmd, t_minishell *minishell)
{
	if (!cmd->cmd || ft_isbuiltin(cmd->cmd))
	{
		ft_execute_builtin(cmd, minishell);
		ft_close_pipes(minishell);
		clean_and_exit(minishell->exit_code);
	}
	else
		ft_execute(cmd, minishell);
}

t_cmd	**ft_cmd_array_converter(t_list *token_list)
{
	t_cmd	**cmds_array;
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
	cmds_array = ft_alloc_lst((i + 1) * sizeof(t_cmd *), 4);
	i = 0;
	tmp = token_list;
	while (tmp)
	{
		if (((t_data_container *)tmp->content)->type == 0)
		{
			cmds_array[i] = (t_cmd *)((t_data_container *)tmp->content)->data;
			i++;
		}
		tmp = tmp->next;
	}
	return (cmds_array);
}

static int	ft_pipex_loop(t_cmd **cmds_array, pid_t *pids, t_minishell *mini)
{
	int	i;

	i = 0;
	while (cmds_array[i])
	{
		pids[i] = fork();
		ft_config_signals_in_exec();
		if (pids[i] < 0)
		{
			ft_dprintf(2, "%s%s: %s%s\n", RED, "fork", strerror(errno), RESET);
			mini->exit_code = 1;
			return (0);
		}
		else if (pids[i] == 0)
			mini_exec(cmds_array[i], mini);
		i++;
	}
	return (1);
}

static void	ft_waiting_loop(pid_t *pids, t_minishell *mini)
{
	int	i;
	int	last_exit_cmd_status;

	i = 0;
	while (pids[i])
	{
		waitpid(pids[i], &last_exit_cmd_status, 0);
		i++;
	}
	if (WIFSIGNALED(last_exit_cmd_status))
		mini->exit_code = (128 + WTERMSIG(last_exit_cmd_status));
	if (WIFEXITED(last_exit_cmd_status))
		mini->exit_code = (WEXITSTATUS(last_exit_cmd_status));
}

void	ft_pipex_and_exec(t_minishell *mini, t_list *token_list)
{
	int		num_of_pipes;
	t_cmd	**cmds_array;
	pid_t	*pids;

	num_of_pipes = ft_pipe_counter(token_list);
	pids = ft_alloc_lst(sizeof(pid_t) * (num_of_pipes + 2), 4);
	cmds_array = ft_cmd_array_converter(token_list);
	if (num_of_pipes || ((*cmds_array)->cmd
			&& !ft_isbuiltin((*cmds_array)->cmd)))
	{
		if (!ft_pipeline(mini, cmds_array, num_of_pipes)
			|| !ft_pipex_loop(cmds_array, pids, mini))
			return ;
		ft_close_pipes(mini);
		ft_waiting_loop(pids, mini);
	}
	else
		ft_execute_builtin(*cmds_array, mini);
}
