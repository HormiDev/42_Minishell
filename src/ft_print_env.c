/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:24:59 by dagimeno          #+#    #+#             */
/*   Updated: 2025/04/01 19:43:44 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief implementacion del comando env que imprime la lista de env
 * 
 * @param env Lista de env
 * @return void
 */
void	ft_print_env(t_list *env, int fd, t_minishell *mini)
{
	while (env)
	{
		if (ft_dprintf(fd, "%s=%s\n", ((t_env *)env->content)->name,
			((t_env *)env->content)->value) == -1)
			return (ft_error_dprintf(mini));
		env = env->next;
	}
	mini->exit_code = 0;
}
