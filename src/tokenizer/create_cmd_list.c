/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 18:13:52 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/05/07 14:35:55 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_create_and_clear_cmds(t_list **list, t_list **cmds, t_list **tmp,
			int *is_cmd)
{
	if (*is_cmd)
	{
		ft_lstadd_back(cmds,
			ft_lstnew_ae(ft_new_data_container(ft_create_cmd(*tmp), 0)));
	}
	if (*list)
		ft_lstadd_back(cmds,
			ft_lstnew_ae(ft_new_data_container
				(ft_strdup_ae((*list)->content), 1)));
	if (*list)
	{
		*tmp = *list;
		*list = (*list)->next;
		(*tmp)->next = NULL;
		ft_free_alloc_lst_clear(tmp, ft_free_alloc);
	}
}

static void	ft_create_cmds_while(t_list **list, t_list **tmp2, int *is_cmd)
{
	while (*list)
	{
		if (!ft_strncmp_p((char *)(*list)->content, "|", 1)
			|| !ft_strncmp_p((char *)(*list)->content, "(", 1)
			|| !ft_strncmp_p((char *)(*list)->content, ")", 1)
			|| !ft_strncmp_p((char *)(*list)->content, "&&", 2)
			|| !ft_strncmp_p((char *)(*list)->content, "\n", 1))
		{
			if (*is_cmd)
				(*tmp2)->next = NULL;
			break ;
		}
		*is_cmd = 1;
		*tmp2 = *list;
		*list = (*list)->next;
	}
}

t_list	*ft_create_cmds(t_list *list)
{
	t_list	*cmds;
	t_list	*tmp;
	t_list	*tmp2;
	int		is_cmd;

	cmds = NULL;
	while (list)
	{
		tmp = list;
		tmp2 = list;
		is_cmd = 0;
		ft_create_cmds_while(&list, &tmp2, &is_cmd);
		ft_create_and_clear_cmds(&list, &cmds, &tmp, &is_cmd);
	}
	return (cmds);
}
