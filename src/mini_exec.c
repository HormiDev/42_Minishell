/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:44:42 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/01/19 22:04:11 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_exec(char *command, char **args, t_minishell *minishell)
{
	if (!ft_strncmp_p(command, "cd", 3))
		ft_cd(args[0], &minishell->envp, &minishell->cwd);
	else if (!ft_strncmp_p(command, "export", 6))
		ft_export_args(args, &minishell->envp);
	else if (!ft_strncmp_p(command, "unset", 5))
		ft_unset_args(args, &minishell->envp);
	else if (!ft_strncmp_p(command, "env", 3))
		ft_print_env(minishell->envp);
	else if (!ft_strncmp_p(command, "exit", 4))
		ft_exit(args);
	else if (!ft_strncmp_p(command, "echo", 4))
		ft_echo(args);
	else if (!ft_strncmp_p(command, "pwd", 3))
		ft_pwd(minishell);
	else
		printf("minishell: %s: command not found\n", command);

}
