/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:18:46 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/04/26 22:04:44 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_init_history(t_minishell *minishell)
{
	char	*home;
	char	history_file[PATH_MAX];

	home = ft_getenv("HOME", minishell->envp);
	if (home)
	{
		ft_sprintf(history_file, "%s/.minishell_history", home);
		minishell->history_fd = open(history_file,
				O_RDWR | O_CREAT | O_APPEND, 0644);
		ft_add_fd_to_alloc_lst_ie(minishell->history_fd);
		if (minishell->history_fd < 0)
			return ;
		home = get_next_line(minishell->history_fd);
		while (home)
		{
			if (home[ft_strlen_p(home) - 1] == '\n')
				home[ft_strlen_p(home) - 1] = '\0';
			add_history(home);
			free(home);
			home = get_next_line(minishell->history_fd);
		}
	}
}
