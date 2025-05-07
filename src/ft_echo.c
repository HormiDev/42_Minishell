/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:04:27 by dagimeno          #+#    #+#             */
/*   Updated: 2025/05/07 14:01:23 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_newline(t_cmd *cmd)
{
	write(cmd->io_fd[1], "\n", 1);
}

static int	is_n_flag(char *arg)
{
	int	i;

	if (!arg)
		return (0);
	if (arg[0] && arg[0] == '-')
	{
		i = 1;
		while (arg[i])
		{
			if (arg[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

void	ft_echo(t_cmd *cmd, t_minishell *mini)
{
	char	flag;
	char	**args;
	int		i;

	mini->exit_code = 0;
	args = &cmd->args[1];
	if (!args[0])
		return (ft_newline(cmd));
	flag = 1;
	i = 0;
	while (is_n_flag(args[i]))
	{
		flag = 0;
		i++;
		if (!args[i])
			return ;
	}
	if (ft_dprintf(cmd->io_fd[1], "%s", args[i++]) == -1)
		return (ft_error_dprintf(mini));
	while (args[i])
		if (ft_dprintf(cmd->io_fd[1], " %s", args[i++]) == -1)
			return (ft_error_dprintf(mini));
	if (flag)
		if (ft_dprintf(cmd->io_fd[1], "\n") == -1)
			return (ft_error_dprintf(mini));
}
