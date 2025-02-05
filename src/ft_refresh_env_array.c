/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_refresh_env_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:15:53 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/02/05 20:10:32 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_refresh_env_array(t_list *list, t_minishell *minishell)
{
	int		i;

	if (minishell->envp_array)
		ft_free_alloc(minishell->envp_array);
	minishell->envp_array = (char **)ft_alloc_lst(sizeof(char *) * (ft_lstsize(list) + 1), 3);
	i = 0;
	while (list)
	{
		minishell->envp_array[i] = ((t_env *)list->content)->full;
		list = list->next;
		i++;
	}
	minishell->envp_array[i] = NULL;
}
