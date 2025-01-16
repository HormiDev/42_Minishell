/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagimeno <dagimeno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:44:42 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/01/15 21:56:14 by dagimeno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_exec(char *comand, t_minishell *minishell)
{
	if (!ft_strncmp_p(comand, "cd", 3))
		{}// ft_cd(comand, minishell);
	else if (!ft_strncmp_p(comand, "export", 6))
		ft_export(comand, &minishell->envp);
	else if (!ft_strncmp_p(comand, "unset", 5))
		{}// ft_unset(comand, &minishell->envp);
	else if (!ft_strncmp_p(comand, "env", 3))
		ft_print_env(minishell->envp);
	else if (!ft_strncmp_p(comand, "exit", 4))
		{}// ft_exit(comand, minishell);
	else if (!ft_strncmp_p(comand, "echo", 4))
		{}// ft_echo(comand, minishell);
	else
		printf("minishell: %s: command not found\n", comand);

}
