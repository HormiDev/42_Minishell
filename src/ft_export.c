/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:32:31 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/01/13 21:43:09 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_export(char *envp, t_list **envp_list)
{
	t_env	*hash;
	int		i;

	i = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	if (!envp[i])
		return ;
	hash = (t_env *)ft_alloc_lst(sizeof(t_env), 3);
	hash->name = ft_substr_ae(envp, 0, i);
	hash->value = ft_strdup_ae(envp + i + 1);
	ft_lstadd_back(envp_list, ft_lstnew_ae(hash));
}