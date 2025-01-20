/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:46:47 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/01/19 21:12:54 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_argument_valid(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] == ' ')
		i++;
	while (ft_isdigit(arg[i]))
		i++;
	while (arg[i] == ' ')
		i++;
	if (arg[i])
		return (0);
	return (1);
}
/**
 * @brief Salir del minishell liberando la memoria y limpiando el historial
 * 
 * @return void
 */
void	ft_exit(char **arg)
{
	unsigned int	pass;
	int				len;
	char			str[256];

	pass = 0;
	ft_printf("exit\n");
	if (arg && arg[0])
	{
		len = ft_splitlen(arg);
		if (!is_argument_valid(arg[0]))
		{
			ft_sprintf(str, "minishell: exit: %s: numeric argument required\n", arg[0]);
			ft_putstr_fd(str, 2);
			exit (2);
		}
		if (len > 1)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return ;
		}
		pass = ft_atoi_p(arg[0]);
	}
	rl_clear_history();
	ft_alloc_lst(0, 0);
	exit(pass);
}
