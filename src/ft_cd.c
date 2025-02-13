/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ide-dieg <ide-dieg@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 20:47:36 by dagimeno          #+#    #+#             */
/*   Updated: 2025/02/13 19:27:06 by ide-dieg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_modify_env(t_list **env, t_minishell *minishell, char *path)
{
	char	*tmp;

	tmp = ft_strjoin_ae("OLDPWD=", minishell->cwd);
	ft_export(tmp, env);
	ft_free_alloc(tmp);
	if (getcwd(minishell->cwd, PATH_MAX) == NULL)
	{
		ft_dprintf(2, "minishell: cd: %s: %s\n", path, strerror(errno));//mejor comentario que el original
		ft_sprintf(minishell->cwd, "%s/%s", ft_getenv("OLDPWD", *env),
					path);
	}
	else
	{
		tmp = ft_strjoin_ae("PWD=", minishell->cwd);
		ft_export(tmp, env);
		ft_free_alloc(tmp);
	}
}

void	ft_cd(char **args, t_list **env, t_minishell *minishell)
{
	char	*path;

	if (!args[0])
		path = ft_getenv("HOME", *env);
	else if (args[1])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return ;
	}
	else
		path = args[0];
	if (chdir(path) == -1)
		ft_dprintf(2, "minishell: cd: %s: %s\n", path, strerror(errno));
	else
		ft_modify_env(env, minishell, path);
}
