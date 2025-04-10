/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save_heredocs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 18:03:29 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/04/10 18:18:36 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_save_heredocs(t_list *cmd_list, t_minishell *minishell)
{
	int 	i;
	t_cmd	*cmd;
	char	heredoc[30];
	int		num_heredocs;

	num_heredocs = 0;
	while (cmd_list)
	{
		if (((t_data_container *)(cmd_list->content))->type == 0)
		{
			cmd = (t_cmd *)((t_data_container *)(cmd_list->content))->data;
			i = 0;
			while (cmd->infiles[i])
			{
				if (cmd->infiles[i]->type == 3)
				{
					ft_sprintf(heredoc, "/tmp/heredoc_%d", num_heredocs);
					ft_lstadd_back(&minishell->here_docs, ft_lstnew_ae(ft_strdup_ae(heredoc)));
					ft_free_alloc(cmd->infiles[i]->file);
					cmd->infiles[i]->file = ft_lstlast(minishell->here_docs)->content;
					cmd->infiles[i]->type = 0;
					num_heredocs++;
				}
				i++;
			}
		}
		cmd_list = cmd_list->next;
	}
}
