/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 11:36:15 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/31 20:46:36 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_close_pipes(t_minishell *minishell)
{
	int	i;

	i = 0;
	while (minishell->pipeline[i])
	{
		close(minishell->pipeline[i][0]);
		close(minishell->pipeline[i][1]);
		i++;
	}
}

/**
 * @brief Crea la pipeline de pipes necesaria para la ejecución de los comandos
 * 
 * @param minishell Estructura principal del programa
 * @return 0 si hay un error, 1 si todo va bien
*/
int ft_pipeline(t_minishell *minishell, t_cmd **cmds, int num_pipes)
{
	int		i;
	
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
		cmds[i]->io_fd[1] = minishell->pipeline[i][1];
		cmds[i + 1]->io_fd[0] = minishell->pipeline[i][0];
		i++;
	}
	return (1);
}
