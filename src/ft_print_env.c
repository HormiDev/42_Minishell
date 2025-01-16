/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:24:59 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/15 23:12:39 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_env(t_list *env)
{
	while (env)
	{
		printf("%s=%s\n", ((t_env *)env->content)->name, ((t_env *)env->content)->value);
		env = env->next;
	}
}
