/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_config_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 12:00:01 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/04/02 13:03:15 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_sig_c(int sig)
{
	(void)sig;
	write(fileno(stdin), "\n", 1);
}

void	ft_config_signals(void)
{
	if (signal(SIGINT, ft_sig_c) == SIG_ERR)
	{
		ft_dprintf(2, "%sError: %s%s\n", RED, strerror(errno), RESET);
		exit(1);
	}
}