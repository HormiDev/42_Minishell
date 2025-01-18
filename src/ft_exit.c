/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:46:47 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/01/18 14:56:11 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/**
 * @brief Salir del minishell liberando la memoria y limpiando el historial
 * 
 * @return void
 */
void	ft_exit(void)
{
	rl_clear_history();
	ft_alloc_lst(0, 0);
	exit(0);
}
