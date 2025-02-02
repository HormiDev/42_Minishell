/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_refresh_env_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:15:53 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/02/02 21:40:18 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_refresh_env_array(t_list *list, char **env_array)
{
	int		i;

	if (env_array)
		ft_free_alloc(env_array);
	env_array = (char **)ft_alloc_lst(sizeof(char *) * ft_lstsize(list) + 1, 3);
	i = 0;
	while (list)
	{
		if 
		env_array[i] = ((t_env *)list->content)->full;
		list = list->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}
