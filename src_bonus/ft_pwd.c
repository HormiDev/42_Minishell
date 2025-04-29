/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:49:32 by dagimeno          #+#    #+#             */
/*   Updated: 2025/04/01 19:52:02 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_pwd(t_cmd *cmd, t_minishell *minishell)
{
	if (ft_dprintf(cmd->io_fd[1], "%s\n", minishell->cwd) == -1)
		return (ft_error_dprintf(minishell));
	minishell->exit_code = 0;
}
