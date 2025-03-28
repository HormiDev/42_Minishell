/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_and_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:26:50 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/28 19:45:46 by ide-dieg         ###   ########.fr       */
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

void	ft_parsing_and_exec(t_minishell *minishell)
{
	t_list	*token_list;
	//t_cmd	*cmd;

	token_list = ft_tokenizer(minishell->line, minishell);
	if (!token_list)
		return ;
	token_list = ft_create_cmds(token_list); //revisar que la lista recibida se libere durante la creacion de los comandos
	//para el bonus aqui se tendra que dividir la lista varias listas partiendo por los || y &&
	//commands_array = ft_cmd_array_converter(token_list);
	// crear funcion de compresion para parentesis que meta todo lo que hay dentro de un parentesis en un solo nodo
	//ft_pipe_counter(token_list);
	//ft_pipeline(minishell, token_list);
	/*
	if (!minishell->num_of_pipes)
	{
		cmd = (t_cmd *)(((t_data_container *)(token_list->content))->data);
		mini_exec(cmd, minishell);
	}
	*/
	if (token_list)
		ft_pipex_and_exec(minishell, token_list);
	/*
	if (token_list && ((t_data_container *)token_list->content)->type == 0)
	{
		cmd = (t_cmd *)(((t_data_container *)(token_list->content))->data);
		mini_exec(cmd, minishell);
	}*/
}
