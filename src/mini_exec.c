/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:44:42 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/01/18 14:55:44 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_exec(char *command, t_minishell *minishell)
{
	if (!ft_strncmp_p(command, "cd", 3))
		{}// ft_cd(command, minishell);
	else if (!ft_strncmp_p(command, "export", 6))
		ft_export(command, &minishell->envp);
	else if (!ft_strncmp_p(command, "unset", 5))
		ft_unset(command, &minishell->envp);
	else if (!ft_strncmp_p(command, "env", 3))
		ft_print_env(minishell->envp);
	else if (!ft_strncmp_p(command, "exit", 4))
		ft_exit();
	else if (!ft_strncmp_p(command, "echo", 4))
		{}// ft_echo(command, minishell);
	else if (!ft_strncmp_p(command, "pwd", 3))
		ft_pwd(minishell);
	else
		printf("minishell: %s: command not found\n", command);

}
