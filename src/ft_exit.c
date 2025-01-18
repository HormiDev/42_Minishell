/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:46:47 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/01/18 17:37:24 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Salir del minishell liberando la memoria y limpiando el historial
 * 
 * @return void
 */
void	ft_exit(char **arg)
{
	unsigned int	pass;

	pass = ft_atoi_p(arg[0]);
	rl_clear_history();
	ft_alloc_lst(0, 0);
	exit(pass);
}
