/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_search_in_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 17:27:58 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/02/02 18:38:28 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_search_in_path(char *cmd, t_list *envp)
{
	char	**path;
	char	*tmp;
	char	*tmp2;
	int		i;

	tmp = ft_getenv("PATH", envp);
	if (!cmd || !envp || !tmp)
		return (cmd);
	path = ft_split_ae(tmp, ':');
	i = 0;
	while (path[i])
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
		i++;
	}
	ft_dprintf(2, "%sminishell: %s: cmd not found%s\n", RED, cmd, RESET);
	return (NULL);
}
