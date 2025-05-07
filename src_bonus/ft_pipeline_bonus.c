/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:47:56 by dagimeno          #+#    #+#             */
/*   Updated: 2025/05/07 14:49:09 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_bonus.h"

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

void	ft_close_pipes(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->pipeline[i])
	{
		ft_close_alloc(minishell->pipeline[i][0]);
		ft_close_alloc(minishell->pipeline[i][1]);
		i++;
	}
}

int	ft_pipeline(t_minishell *minishell, t_cmd **cmds, int num_pipes)
{
	int	i;

	minishell->pipeline = ft_alloc_lst(sizeof(int *) * (num_pipes + 1), 4);
	i = 0;
	while (i < num_pipes)
	{
		minishell->pipeline[i] = ft_alloc_lst(sizeof(int) * 2, 4);
		if (pipe(minishell->pipeline[i]) == -1)
		{
			ft_close_pipes(minishell);
			perror("pipe error");
			minishell->exit_code = 129;
			return (0);
		}
		ft_add_fd_to_alloc_lst_ie(minishell->pipeline[i][0]);
		ft_add_fd_to_alloc_lst_ie(minishell->pipeline[i][1]);
		cmds[i]->io_fd[1] = minishell->pipeline[i][1];
		cmds[i + 1]->io_fd[0] = minishell->pipeline[i][0];
		i++;
	}
	return (1);
}
