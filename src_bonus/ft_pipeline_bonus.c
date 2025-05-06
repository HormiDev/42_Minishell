/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:47:56 by dagimeno          #+#    #+#             */
/*   Updated: 2025/05/06 22:50:51 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_bonus.h"

void	ft_close_pipes(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->pipeline[i])
	{
		ft_close_alloc(minishell->pipeline[i][0]);
		ft_close_alloc(minishell->pipeline[i][1]);
		i++;
	}
}

/**
 * @brief Crea la pipeline de pipes necesaria para la ejecución de los comandos
 * 
 * @param minishell Estructura principal del programa
 * @return 0 si hay un error, 1 si todo va bien
*/
int	ft_pipeline(t_minishell *minishell, t_cmd **cmds, int num_pipes)
{
	int	i;

	minishell->pipeline = ft_alloc_lst(sizeof(int *) * (num_pipes + 1), 4);
	i = 0;
	while (i < num_pipes)
	{
		minishell->pipeline[i] = ft_alloc_lst(sizeof(int) * 2, 4);
		if (pipe(minishell->pipeline[i]) == -1)
		{
			ft_close_pipes(minishell);
			perror("pipe error");
			minishell->exit_code = 129;
			return (0);
		}
		ft_add_fd_to_alloc_lst_ie(minishell->pipeline[i][0]);
		ft_add_fd_to_alloc_lst_ie(minishell->pipeline[i][1]);
		cmds[i]->io_fd[1] = minishell->pipeline[i][1];
		cmds[i + 1]->io_fd[0] = minishell->pipeline[i][0];
		i++;
	}
	return (1);
}
