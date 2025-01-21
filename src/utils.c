/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:40:52 by dagimeno          #+#    #+#             */
/*   Updated: 2025/01/21 14:53:35 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	clean_and_exit(int exit_code)
{
	//rl_clear_history();
	ft_alloc_lst(0, 0);
	exit(exit_code);
}