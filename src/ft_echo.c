/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:04:27 by dagimeno          #+#    #+#             */
/*   Updated: 2025/03/10 19:58:04 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_echo(char **args, t_minishell *mini)
{
	char	flag;
	int		i;

	flag = 1;
	i = 0;
	if (!args[0])
		return ;
	if (ft_strncmp_p(args[0], "-n", 3) == 0)
	{
		flag = 0;
		i++;
	}
	ft_dprintf(mini->io_fd[1], "%s", args[i++]);
	while (args[i])
		ft_dprintf(mini->io_fd[1], " %s", args[i++]);
	if (flag)
		ft_dprintf(mini->io_fd[1], "\n");
}

