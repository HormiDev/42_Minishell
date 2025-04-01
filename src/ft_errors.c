/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:35:53 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/04/01 19:38:22 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_error_dprintf(t_minishell *minishell)
{
	ft_dprintf(2, "%s%s: %s%s\n", RED, "minishell", strerror(errno), RESET);
	minishell->exit_code = 1;
}