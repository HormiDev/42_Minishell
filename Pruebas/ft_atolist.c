/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atolist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:06:40 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/13 20:13:18 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


t_envp	*ft_atolist(char **envpp)
{
	t_envp	*head;
	t_envp	*node;
	int		i;
	int		j;

	i = 0;
	while (envp[i])
	{
		node = (t_envp *)ft_alloc_lst(sizeof(t_envp), 4);
		node->line = ft_strdup_ae(envp[i]);
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		node->key = ft_substr_ae(envp[i], 0, j);
		node->value = ft_strdup_ae(envp[i] + j + 1);
		if (i == 0)
			head = node;
		else
			ft_lstadd_back((t_list **)&head, (t_list *)node);
	}
	return (head);
}
