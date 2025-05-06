/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 19:30:13 by dagimeno          #+#    #+#             */
/*   Updated: 2025/05/06 21:30:26 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_bonus.h"

void	ft_error_dprintf(t_minishell *minishell)
{
	ft_dprintf(2, "%s%s: %s%s\n", RED, "minishell", strerror(errno), RESET);
	minishell->exit_code = 1;
}
