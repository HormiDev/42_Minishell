/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_prompt.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 19:52:44 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/01/18 14:55:49 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Actualiza el prompt del minishell modificando el cwd_short en caso de
 * que el home exista en el envairoment y el inicio del cwd sea igual al home
 * 
 * @param minishell Estructura del minishell
 * @return void
 */
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
