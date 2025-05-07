/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_and_exec_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:47:08 by dagimeno          #+#    #+#             */
/*   Updated: 2025/05/07 13:27:13 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_bonus.h"

void	ft_print_cmdlist(t_list *cmds);
void	ft_print(t_list *list);
void	ft_print_cmd(t_cmd *cmd);
//no olvidar borrar estas funciones cuando hayamos hecho todo

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

int	ft_and_or_counter(t_list *token_list)
{
	int		and_or_count;

	and_or_count = 0;
	while (token_list)
	{
		if (((t_data_container *)token_list->content)->type == 1
			&& (!ft_strncmp_p((char *)
					((t_data_container *)token_list->content)->data, "&&", 2)
				|| !ft_strncmp_p((char *)
					((t_data_container *)token_list->content)->data, "||", 2)))
			and_or_count++;
		token_list = token_list->next;
	}
	return (and_or_count);
}

void	ft_and_or(t_minishell *mini, t_list **and_or_list)
{
	int		i;

	i = -1;
	while (and_or_list[++i] && mini->exit_code != 130)
	{
		if (((t_data_container *)(and_or_list[i]->content))->type != 1)
			ft_pipex_and_exec(mini, and_or_list[i]);
		else if (((t_data_container *)(and_or_list[i]->content))->type == 1)
		{
			if (!ft_strncmp_p((char *)((t_data_container *)
					(and_or_list[i]->content))->data, "&&", 2))
			{
				if (mini->exit_code == 0)
					ft_pipex_and_exec(mini, and_or_list[i]->next);
			}
			else if (!ft_strncmp_p((char *)((t_data_container *)
					(and_or_list[i]->content))->data, "||", 2))
			{
				if (mini->exit_code != 0)
					ft_pipex_and_exec(mini, and_or_list[i]->next);
				else
					mini->exit_code = 0;
			}
		}
	}
}

void	ft_parsing_and_exec(t_minishell *mini)
{
	t_list	*token_list;
	t_list	**and_or_list;

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
	ft_capsule_parentesis(token_list);
	and_or_list = ft_split_and_or(token_list);
	mini->exit_code = 0;
	ft_and_or(mini, and_or_list);
	ft_clear_here_docs(mini);
}
