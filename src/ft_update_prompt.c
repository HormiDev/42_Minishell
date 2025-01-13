/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:52:44 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/01/13 20:25:12 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_update_prompt(t_minishell *minishell)
{
	ft_sprintf(minishell->prompt, "%s%s@%s%s:%s%s%s$ ", BOLD, minishell->user,
		minishell->host, RESET, YELLOW, minishell->cwd, RESET);
}
