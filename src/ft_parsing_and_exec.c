/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_and_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:26:50 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/05/07 13:09:28 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_cmdlist(t_list *cmds);
void	ft_print(t_list *list);
void	ft_print_cmd(t_cmd *cmd);
//no olvidar borrar estas funciones cuando hayamos hecho todo

int	ft_count_pipes(t_list *token_list)
{
	int		count;
	t_list	*tmp;

	count = 0;
	tmp = token_list;
	while (tmp)
	{
		if (((t_data_container *)tmp->content)->type == 0)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	ft_pipe_counter(t_list *token_list)
{
	int					count;
	t_list				*tmp;
	t_data_container	*tmp_data;

	count = 0;
	tmp = token_list;
	while (tmp)
	{
		tmp_data = (t_data_container *)tmp->content;
		if (tmp_data->type == 1 && ((char *)tmp_data->data)[0] == '|'
			&& ((char *)tmp_data->data)[1] == '\0')
			count++;
		tmp = tmp->next;
	}
	return (count);
}

static void	ft_print_error_and_exit(void)
{
	ft_dprintf(2, "%sError: %s%s\n", RED, strerror(errno), RESET);
	clean_and_exit(1);
}

static int	exec_heredocs(t_list *token_list, t_minishell *mini)
{
	pid_t	herdoc_pid;
	int		here_fork_status;

	herdoc_pid = fork();
	if (herdoc_pid == -1)
		ft_print_error_and_exit();
	if (herdoc_pid == 0)
	{
		ft_config_signals_in_heredoc();
		ft_create_heredocs(token_list, mini);
		clean_and_exit(0);
	}
	ft_save_heredocs(token_list, mini);
	if (waitpid(herdoc_pid, &here_fork_status, 0) == -1)
		ft_print_error_and_exit();
	if (WIFSIGNALED(here_fork_status))
	{
		ft_clear_here_docs(mini);
		ft_free_alloc_lst_clear(&token_list, ft_free_alloc);
		mini->exit_code = (128 + WTERMSIG(here_fork_status));
		return (0);
	}
	return (1);
}

void	ft_parsing_and_exec(t_minishell *mini)
{
	t_list	*token_list;

	token_list = ft_tokenizer(mini->line, mini);
	if (!token_list)
		return ;
	token_list = ft_create_cmds(token_list);
	if (token_list)
	{
		ft_config_signals_in_exec();
		if (!exec_heredocs(token_list, mini))
			return ;
	}
	if (token_list)
		ft_pipex_and_exec(mini, token_list);
	ft_clear_here_docs(mini);
}
