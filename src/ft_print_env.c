/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:24:59 by dagimeno          #+#    #+#             */
/*   Updated: 2025/03/03 17:51:06 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief implementacion del comando env que imprime la lista de env
 * 
 * @param env Lista de env
 * @return void
 */
void	ft_print_env(t_list *env, int fd)
{
	while (env)
	{
		ft_dprintf(fd, "%s=%s\n", ((t_env *)env->content)->name, ((t_env *)env->content)->value);
		env = env->next;
	}
}
