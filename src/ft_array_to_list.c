/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_to_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 21:31:23 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/01/13 22:06:46 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_array_to_list(char **envp, t_list **envp_list)
{
	int		i;

	i = 0;
	while (envp[i])
		ft_export(envp[i++], envp_list);
}
