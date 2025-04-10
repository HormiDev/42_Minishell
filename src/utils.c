/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:40:52 by dagimeno          #+#    #+#             */
/*   Updated: 2025/04/10 18:11:26 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isnumber(char *str)
{
	int		i;

	i = 0;
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] && (str[i] != ' ' || (str[i] > 8 && str[i] < 14)))
		return(0);
	while (str[i] == ' ' || (str[i] > 8 && str[i] < 14))
		i++;
	if (str[i] && (str[i] != ' ' || (str[i] > 8 && str[i] < 14)))
		return(0);
	return (1);
}

void	clean_and_exit(int exit_code)
{
	rl_clear_history();
	ft_alloc_lst(0, 0);
	exit(exit_code);
}