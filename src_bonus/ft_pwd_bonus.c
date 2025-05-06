/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:49:40 by dagimeno          #+#    #+#             */
/*   Updated: 2025/05/06 22:50:51 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_bonus.h"

void	ft_pwd(t_cmd *cmd, t_minishell *minishell)
{
	if (ft_dprintf(cmd->io_fd[1], "%s\n", minishell->cwd) == -1)
		return (ft_error_dprintf(minishell));
	minishell->exit_code = 0;
}
