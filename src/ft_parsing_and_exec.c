/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_and_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:26:50 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/04/10 18:35:38 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_cmdlist(t_list *cmds);
void	ft_print(t_list *list);
void	ft_print_cmd(t_cmd *cmd);

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
		if (tmp_data->type == 1 && ((char *)tmp_data->data)[0] == '|' && ((char *)tmp_data->data)[1] == '\0')
			count++;
		tmp = tmp->next;
	}
	return (count);
}

void	ft_parsing_and_exec(t_minishell *mini)
{
	t_list	*token_list;
	//t_cmd	*cmd;
	pid_t	herdoc_pid;
	int		here_fork_status;

	token_list = ft_tokenizer(mini->line, mini);
	if (!token_list)
		return ;
	//ft_print(token_list);
	token_list = ft_create_cmds(token_list); //revisar que la lista recibida se libere durante la creacion de los comandos
	if (token_list)
	{
		ft_config_signals_in_exec();
		herdoc_pid = fork();
		if (herdoc_pid == -1)
		{	
			ft_dprintf(2, "%sError: %s%s\n", RED, strerror(errno), RESET);
			clean_and_exit(1);
		}
		if (herdoc_pid == 0)
		{
			ft_config_signals_in_heredoc();
			ft_create_heredocs(token_list, mini);
			exit(0);
		}
		ft_save_heredocs(token_list, mini);
		if (waitpid(herdoc_pid, &here_fork_status, 0) == -1)
		{
			ft_dprintf(2, "%sError: %s%s\n", RED, strerror(errno), RESET);
			clean_and_exit(1);
		}
		if (WIFSIGNALED(here_fork_status))
		{
			ft_clear_here_docs(mini);
			ft_free_alloc_lst_clear(&token_list, ft_free_alloc);
			mini->exit_code = (128 + WTERMSIG(here_fork_status));
			return ;
		}
	}
	//para el bonus aqui se tendra que dividir la lista varias listas partiendo por los || y &&
	//commands_array = ft_cmd_array_converter(token_list);
	// crear funcion de compresion para parentesis que meta todo lo que hay dentro de un parentesis en un solo nodo
	//ft_pipe_counter(token_list);
	//ft_pipeline(mini, token_list);
	/*
	if (!mini->num_of_pipes)
	{
		cmd = (t_cmd *)(((t_data_container *)(token_list->content))->data);
		mini_exec(cmd, mini);
	}
	*/
	if (token_list)
		ft_pipex_and_exec(mini, token_list);
	ft_clear_here_docs(mini);
	/*
	if (token_list && ((t_data_container *)token_list->content)->type == 0)
	{
		cmd = (t_cmd *)(((t_data_container *)(token_list->content))->data);
		mini_exec(cmd, mini);
	}*/
}
