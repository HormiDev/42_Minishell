/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:52:44 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/01/16 00:48:23 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_update_prompt(t_minishell *minishell)
{
	char	*home;

	home = ft_getenv("HOME", minishell->envp);
	if (!home && ft_strncmp_p(home, minishell->cwd, ft_strlen_p(home)))
		ft_strlcpy(minishell->cwd_short, minishell->cwd, PATH_MAX);
	else
		ft_sprintf(minishell->cwd_short, "~%s",
			minishell->cwd + ft_strlen_p(home));
	ft_sprintf(minishell->prompt, "%s%s%s@%s%s:%s%s%s$ ",
		CYAN, BOLD, minishell->user,
		minishell->host, RESET, YELLOW, minishell->cwd_short, RESET);
}
