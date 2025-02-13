/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_and_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:26:50 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/02/13 18:51:31 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_parsing_and_exec(t_minishell *minishell)
{
	char	**args;
	char	*command;

	args = ft_split_ae(minishell->line, ' ');// sustituir por parseo
	command = args[0];
	mini_exec(command, args, minishell);
}