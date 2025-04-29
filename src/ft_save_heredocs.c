/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:03:29 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/04/29 21:42:15 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_loop_through_infiles(t_cmd *cmd, t_minishell *mini)
{
	int			i;
	char		heredoc[30];
	static int	num = 0;

	i = 0;
	while (cmd->infiles[i])
	{
		if (cmd->infiles[i]->type == 3)
		{
			ft_snprintf(heredoc, 30, "/tmp/heredoc_%d", num);
			ft_lstadd_back(&mini->here_docs,
				ft_lstnew_ae(ft_strdup_ae(heredoc)));
			ft_free_alloc(cmd->infiles[i]->file);
			cmd->infiles[i]->file = ft_lstlast(mini->here_docs)->content;
			cmd->infiles[i]->type = 0;
			num++;
		}
		i++;
	}
}

void	ft_save_heredocs(t_list *cmd_list, t_minishell *minishell)
{
	t_cmd	*cmd;

	while (cmd_list)
	{
		if (((t_data_container *)(cmd_list->content))->type == 0)
		{
			cmd = (t_cmd *)((t_data_container *)(cmd_list->content))->data;
			ft_loop_through_infiles(cmd, minishell);
		}
		cmd_list = cmd_list->next;
	}
}
