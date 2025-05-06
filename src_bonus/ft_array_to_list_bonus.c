/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_to_list_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:23:33 by dagimeno          #+#    #+#             */
/*   Updated: 2025/05/06 21:24:49 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_bonus.h"

void	ft_array_to_list(char **envp, t_list **envp_list)
{
	int	i;

	i = 0;
	while (envp[i])
		ft_export(envp[i++], envp_list);
}
