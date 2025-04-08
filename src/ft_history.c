/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 23:18:46 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/04/08 23:56:36 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_init_history(t_minishell *minishell)
{
    char *home;
    char history_file[PATH_MAX];

    home = ft_getenv("HOME", minishell->envp);
    if (home)
    {
        ft_sprintf(history_file, "%s/.minishell_history", home);
        minishell->history_fd = open(history_file, O_RDWR | O_CREAT | O_APPEND, 0644);
        if (minishell->history_fd < 0)
        {
            ft_dprintf(2, "%s%s: %s%s\n", RED, "open", strerror(errno), RESET);
            ft_alloc_lst(0, 0);
            minishell->exit_code = 1;
        }
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
