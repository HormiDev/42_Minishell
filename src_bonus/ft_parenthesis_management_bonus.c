/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parenthesis_management_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:52:49 by dagimeno          #+#    #+#             */
/*   Updated: 2025/05/07 13:39:42 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_bonus.h"

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
