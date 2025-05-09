/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 12:28:53 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/05/07 13:10:35 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_main_loop(t_minishell *minishell)
{
	while (1)
	{
		ft_update_prompt(minishell);
		minishell->line = readline(minishell->prompt);
		if (!minishell->line)
		{
			minishell->line = ft_strdup_ae("exit");
			ft_parsing_and_exec(minishell);
		}
		else
			ft_add_to_alloc_lst_e(minishell->line);
		if (*minishell->line)
		{
			add_history(minishell->line);
			ft_dprintf(minishell->history_fd, "%s\n", minishell->line);
			ft_parsing_and_exec(minishell);
		}
		ft_free_alloc((minishell->line));
		ft_config_signals();
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*minishell;

	if (argc != 1 || !argv)
		return (ft_putstr_fd("Error: invalid arguments\n", 2), 1);
	ft_add_exit_function(clear_history);
	minishell = ft_loading_minishell(envp);
	ft_config_signals();
	ft_main_loop(minishell);
	rl_clear_history();
	ft_alloc_clear();
}
