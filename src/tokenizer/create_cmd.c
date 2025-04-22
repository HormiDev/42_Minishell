/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 20:32:45 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/28 19:43:43 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Funcion que cuenta el numero de redirecciones y comandos en una lista
 * 0 = <, 1 = >, 2 = cmd
 */
static void	ft_count_arrays(t_list *list, int *cmd_redir_count)
{
	while (list)
	{
		if (!ft_strncmp_p((char *)list->content, "<", 1))
			cmd_redir_count[0]++;
		else if (!ft_strncmp_p((char *)list->content, ">", 1))
			cmd_redir_count[1]++;
		else
			cmd_redir_count[2]++;
		list = list->next;
	}
}

static t_redir	*ft_create_redir(char *str)
{
	t_redir	*new_redir;

	new_redir = ft_alloc_lst(sizeof(t_redir), 4);
	if (!ft_strncmp_p(str, ">>", 2))
	{
		new_redir->type = 2;
		new_redir->file = ft_substr_ae(str, 3, ft_strlen_p(str) - 4);
	}
	else if (!ft_strncmp_p(str, ">", 1))
	{
		new_redir->type = 1;
		new_redir->file = ft_substr_ae(str, 2, ft_strlen_p(str) - 3);
	}
	else if (!ft_strncmp_p(str, "<<", 2))
	{
		new_redir->type = 3;
		new_redir->file = ft_substr_ae(str, 3, ft_strlen_p(str) - 4);
	}
	else
	{
		new_redir->type = 0;
		new_redir->file = ft_substr_ae(str, 2, ft_strlen_p(str) - 3);
	}
	return (new_redir);
}

static void	ft_create_cmd_while(t_list *list, t_cmd *new_cmd, int *counts)
{
	if (!ft_strncmp_p((char *)list->content, "<", 1))
	{
		new_cmd->infiles[counts[0]] = ft_create_redir((char *)list->content);
		counts[0]++;
	}
	else if (!ft_strncmp_p((char *)list->content, ">", 1))
	{
		new_cmd->outfiles[counts[1]] = ft_create_redir((char *)list->content);
		counts[1]++;
	}
	else
	{
		new_cmd->args[counts[2]] = ft_substr_ae((char *)list->content, 1,
				ft_strlen_p((char *)list->content) - 2);
		counts[2]++;
	}
}

t_cmd	*ft_create_cmd(t_list *list)
{
	t_cmd	*new_cmd;
	int		counts[3];

	ft_memset(counts, 0, 3 * sizeof(int));
	new_cmd = ft_alloc_lst(sizeof(t_cmd), 4);
	ft_count_arrays(list, counts);
	new_cmd->args = ft_alloc_lst((counts[2] + 1) * sizeof(char *), 4);
	new_cmd->infiles = ft_alloc_lst((counts[0] + 1) * sizeof(t_redir *), 4);
	new_cmd->outfiles = ft_alloc_lst((counts[1] + 1) * sizeof(t_redir *), 4);
	new_cmd->io_fd[0] = 0;
	new_cmd->io_fd[1] = 1;
	ft_memset(counts, 0, 3 * sizeof(int));
	while (list)
	{
		ft_create_cmd_while(list, new_cmd, counts);
		list = list->next;
	}
	new_cmd->cmd = new_cmd->args[0];
	return (new_cmd);
}
