/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:31:01 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/18 14:55:58 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void   ft_unset(char *envp, t_list **env_list)
{
	t_list	*tmp_list;

	tmp_list = *env_list;
	if (!envp || !env_list)
		return ;
	if (!ft_strncmp_p(((t_env *)tmp_list->content)->name, envp,
			ft_strlen_p(envp) + 1))
	{
		*env_list = tmp_list->next;
		return ;
	}
	while (tmp_list->next)
	{
		if (!ft_strncmp_p(((t_env *)tmp_list->next->content)->name, envp,
			ft_strlen_p(envp) + 1))
		{
			tmp_list->next = tmp_list->next->next;
			return ;
		}
		tmp_list = tmp_list->next;
	}
}
