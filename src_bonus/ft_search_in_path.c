/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_in_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:27:58 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/03/03 17:06:29 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_search_in_path(char *cmd, t_minishell *minishell)
{
	char	**path;
	char	*tmp;
	char	*tmp2;
	int		i;

	tmp = ft_getenv("PATH", minishell->envp);
	if (!cmd || !minishell->envp || !tmp)
		return (cmd);
	path = ft_split_ae(tmp, ':');
	i = -1;
	while (path[++i])
	{
		tmp2 = ft_strjoin_ae(path[i], "/");
		tmp = ft_strjoin_ae(tmp2, cmd);
		if (!access(tmp, X_OK))
		{
			ft_free_alloc(tmp2);
			ft_free_alloc(path);
			return (tmp);
		}
		ft_free_alloc(tmp);
	}
	ft_dprintf(2, "%sminishell: %s: cmd not found%s\n", RED, cmd, RESET);
	minishell->exit_code = 127;
	return (NULL);
}
