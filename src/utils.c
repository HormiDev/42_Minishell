/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:40:52 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/24 15:17:49 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_and_exit(int exit_code)
{
	//rl_clear_history();
	ft_alloc_lst(0, 0);
	exit(exit_code);
}