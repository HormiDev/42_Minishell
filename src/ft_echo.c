/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 13:04:27 by dagimeno          #+#    #+#             */
/*   Updated: 2025/03/03 17:49:42 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_echo(char **args)
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
	ft_printf("%s", args[i++]);
	while (args[i])
		ft_printf(" %s", args[i++]);
	if (flag)
		ft_printf("\n");
}

