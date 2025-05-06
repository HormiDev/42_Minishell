/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 20:16:10 by dagimeno          #+#    #+#             */
/*   Updated: 2025/05/06 22:16:14 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell_bonus.h"

static int	is_argument_valid(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] == ' ')
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	if (!ft_isdigit(arg[i]))
		return (0);
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
void	ft_exit(char **arg, t_minishell *minishell)
{
	int				len;

	ft_printf("exit\n");
	if (arg && arg[0])
	{
		len = ft_splitlen(arg);
		if (!is_argument_valid(arg[0]))
		{
			ft_dprintf(2, "minishell: exit: ");
			ft_dprintf(2, "%s: numeric argument required\n", arg[0]);
			clean_and_exit(2);
		}
		if (len > 1)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return ;
		}
	}
	ft_free_alloc((minishell->line));
	minishell->line = NULL;
	clean_and_exit((unsigned int)ft_atoi_p(arg[0]));
}
