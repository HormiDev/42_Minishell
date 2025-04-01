/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:04:27 by dagimeno          #+#    #+#             */
/*   Updated: 2025/04/01 19:41:33 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//void	ft_echo(char **args, t_minishell *mini)
void	ft_echo(t_cmd *cmd, t_minishell *mini)
{
	char	flag;
	char	**args;
	int		i;

	args = &cmd->args[1];
	if (!args[0])
		return ;
	flag = 1;
	i = 0;
	if (ft_strncmp_p(args[0], "-n", 3) == 0)
	{
		flag = 0;
		i++;
	}
	if (ft_dprintf(cmd->io_fd[1], "%s", args[i++]) == -1)
		return (ft_error_dprintf(mini));
	while (args[i])
		if (ft_dprintf(cmd->io_fd[1], " %s", args[i++]) == -1)
			return (ft_error_dprintf(mini));
	if (flag)
		if (ft_dprintf(cmd->io_fd[1], "\n") == -1)
			return (ft_error_dprintf(mini));
	mini->exit_code = 0;
}

