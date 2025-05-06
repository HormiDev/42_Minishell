/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_and_exec_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:47:08 by dagimeno          #+#    #+#             */
/*   Updated: 2025/05/07 00:06:52 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_bonus.h"

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

static void	ft_split_and_or_loop(t_list **token_list, t_list **prev)
{
	while (*token_list)
	{
		if (((t_data_container *)(*token_list)->content)->type == 1
			&& (!ft_strncmp_p((char *)
					((t_data_container *)(*token_list)->content)->data,
					"&&", 2)
				|| !ft_strncmp_p((char *)
					((t_data_container *)(*token_list)->content)->data,
					"||", 2)))
			return ;
		*prev = *token_list;
		*token_list = (*token_list)->next;
	}
}

t_list	**ft_split_and_or(t_list *token_list)
{
	int		and_or_count;
	t_list	**split_and_or;
	t_list	*prev;
	int		i;

	and_or_count = ft_and_or_counter(token_list);
	split_and_or = (t_list **)ft_alloc_lst
		(sizeof(t_list *) * (and_or_count + 2), 4);
	i = 0;
	split_and_or[i] = token_list;
	while (i < and_or_count)
	{
		ft_split_and_or_loop(&token_list, &prev);
		prev->next = NULL;
		i++;
		split_and_or[i] = token_list;
		if (token_list)
			token_list = token_list->next;
	}
	return (split_and_or);
}

t_cmd	*fill_info(t_list **open, t_list **after_close, t_list **tk_list)
{
	t_cmd	*cmd;
	
	(*open)->next = (*after_close)->next->next;
	(*after_close)->next = 0;
	cmd = ft_alloc_lst(sizeof(t_cmd), 4);
	cmd->args = ft_alloc_lst(1 * sizeof(char *), 4);
	cmd->infiles = ft_alloc_lst(1 * sizeof(t_redir *), 4);
	cmd->outfiles = ft_alloc_lst(1 * sizeof(t_redir *), 4);
	cmd->and_or_list = ft_split_and_or
		(((t_data_container *)(*open)->content)->data);
	cmd->io_fd[0] = 0;
	cmd->io_fd[1] = 1;
	((t_data_container *)(*open)->content)->data = cmd;
	*tk_list = *open;
	return (cmd);
}

t_list	*ft_capsule_parentesis(t_list *tk_list)
{
	t_list	*open;
	t_list	*after_close;
	t_list	*tmp_prev;
	t_cmd	*cmd;

	tmp_prev = tk_list;
	while (tk_list)
	{
		if (((t_data_container *)tk_list->content)->type == 1
			&& *(char *)(((t_data_container *)tk_list->content)->data) == '(')
		{
			open = tk_list;
			((t_data_container *)open->content)->data = open->next;
			((t_data_container *)open->content)->type = 2;
			after_close = ft_capsule_parentesis(tk_list->next);
			cmd = fill_info(&open, &after_close, &tk_list);
			/*open->next = after_close->next->next;
			after_close->next = 0;
			cmd = ft_alloc_lst(sizeof(t_cmd), 4);
			cmd->args = ft_alloc_lst(1 * sizeof(char *), 4);
			cmd->infiles = ft_alloc_lst(1 * sizeof(t_redir *), 4);
			cmd->outfiles = ft_alloc_lst(1 * sizeof(t_redir *), 4);
			cmd->and_or_list = ft_split_and_or
				(((t_data_container *)open->content)->data);
			cmd->io_fd[0] = 0;
			cmd->io_fd[1] = 1;
			((t_data_container *)open->content)->data = cmd;
			tk_list = open;*/
		}
		else if (((t_data_container *)tk_list->content)->type == 1
			&& *(char *)(((t_data_container *)tk_list->content)->data) == ')')
			return (tmp_prev);
		tmp_prev = tk_list;
		if (tk_list)
			tk_list = tk_list->next;
	}
	return (0);
}

void	ft_and_or(t_minishell *mini, t_list **and_or_list)
{
	int		i;

	i = 0;
	while (and_or_list[i] && mini->exit_code != 130)
	{
		//ft_print_cmdlist(and_or_list[i]);
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
			else if (!ft_strncmp_p((char *)((t_data_container *)(and_or_list[i]->content))->data,
				"||", 2))
			{
				if (mini->exit_code != 0)
					ft_pipex_and_exec(mini, and_or_list[i]->next);
				else
					mini->exit_code = 0;
			}
		}
		i++;
	}
}

void	ft_parsing_and_exec(t_minishell *mini)
{
	t_list	*token_list;
	t_list	**and_or_list;

	token_list = ft_tokenizer(mini->line, mini);
	if (!token_list)
		return ;
	//ft_print(token_list);
	//and_or_list = ft_create_and_or_list(token_list);
	token_list = ft_create_cmds(token_list); //revisar que la lista recibida se libere durante la creacion de los comandos
	if (token_list)
	{
		ft_config_signals_in_exec();
		if (!exec_heredocs(token_list, mini))//revisar nombre de funcion, es confuso
			return ;
	}
	//para el bonus aqui se tendra que dividir la lista varias listas partiendo por los || y &&
	ft_capsule_parentesis(token_list);
	and_or_list = ft_split_and_or(token_list);
	//ft_print_and_or_list(and_or_list);
	//ft_printf("hola\n");
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
	mini->exit_code = 0;
	ft_and_or(mini, and_or_list);
	ft_clear_here_docs(mini);
	/*
	if (token_list && ((t_data_container *)token_list->content)->type == 0)
	{
		cmd = (t_cmd *)(((t_data_container *)(token_list->content))->data);
		mini_exec(cmd, mini);
	}*/
}
