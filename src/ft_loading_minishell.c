/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_loading_minishell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 17:30:21 by ide-dieg          #+#    #+#             */
/*   Updated: 2025/01/13 20:25:12 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_current(char *user_name)
{
	char	*cwd;
	char	**split;
	char	*join;
	int		i;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	split = ft_split_ae(cwd, '/');
	if (split[0] && !ft_strncmp_p(split[0], "home", 5) && split[1]
		&& !ft_strncmp_p(split[1], user_name, ft_strlen_p(user_name) + 1))
	{
		join = ft_strdup_ae("~");
		i = 2;
		while (split[i])
		{
			join = ft_strjoin_ae(join, "/");
			join = ft_strjoin_ae(join, split[i++]);
		}
		free(cwd);
		return (join);
	}
	return (cwd);
}

static char	*get_hostname(char **envp)
{// proteger funcion y liverar memoria
	char	*session_manager;
	char	**split;
	char	**split2;

	session_manager = ft_getenv("SESSION_MANAGER", envp);
	if (!session_manager)
		return (NULL);
	split = ft_split_ae(session_manager, '/');
	split2 = ft_split_ae(split[1], '.');
	return (ft_strdup_ae(split2[0]));
}

t_minishell	*ft_loading_minishell(char **envp)
{
	t_minishell	*minishell;

	minishell = ft_alloc_lst(sizeof(t_minishell), 4);
	if (envp)
	{// revisar protecciones
		minishell->envp = envp;// crear copia de envp en forma de lista
		minishell->user = ft_strdup_ae(ft_getenv("USER", envp));
		minishell->host = get_hostname(envp);
	}
	else
	{
		minishell->envp = NULL;// crear nuevo envp
		minishell->user = ft_strdup_ae("ide-dieg");
		minishell->host = ft_strdup_ae("dagimeno");
	}
	minishell->cwd = get_current(minishell->user);
	return (minishell);
}
